package com.example.gabri.tccv1;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.io.IOException;
import java.util.List;
import java.util.Locale;

public class EstadoPaciente extends AppCompatActivity {

    String str_telefone, longitude, latitude,localizacao_atual;
    double d_latitude,d_longitude;
    private LocationManager locationManager = null;
    private LocationListener locationListener = null;

    Geocoder geocoder;
    List<Address> addresses;

    @SuppressLint("MissingPermission")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_estado_paciente);
        SharedPreferences sharedPref = getSharedPreferences("telefone_contato", Context.MODE_PRIVATE);
        str_telefone = sharedPref.getString("telefone_contato", "sem_cadastro");

        locationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        locationListener = new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                longitude = " Longitude: " + location.getLongitude();
                latitude = " Latitude: " + location.getLatitude();
                d_latitude = location.getLatitude();
                d_longitude = location.getLongitude();
            }

            @Override
            public void onStatusChanged(String provider, int status, Bundle extras) {

            }

            @Override
            public void onProviderEnabled(String provider) {

            }

            @Override
            public void onProviderDisabled(String provider) {

            }
        };

        locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 0, locationListener);

        geocoder = new Geocoder(this, Locale.ENGLISH);
        try {
            addresses = geocoder.getFromLocation(d_latitude,d_longitude,2);
            if(addresses != null && addresses.size() > 0){
                localizacao_atual = addresses.get(0).getAddressLine(0);
                Toast.makeText(this, "entrei aqui", Toast.LENGTH_LONG).show();

            }

        } catch (IOException e) {
            e.printStackTrace();
        }



        Button b_sim = (Button) findViewById(R.id.b_sim); // Botão de sim
        b_sim.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                sendSMS(str_telefone,"Estou bem");
            }
        });

        Button b_nao = (Button) findViewById(R.id.b_nao); // Botão de não
        b_nao.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {

                if(str_telefone.equals("sem_cadatro")){

                    Toast.makeText(v.getContext(), "Cadastre um contato de emergência", Toast.LENGTH_LONG).show();
                    Intent i = new Intent(v.getContext(), EditarContato.class);
                    startActivity(i);// Vai para Activity Editar Contato

                }else{
                    sendSMS(str_telefone, "SOCORROOO!!!!" + longitude + latitude + localizacao_atual);

                }
            }
        });


    }

    private void sendSMS(String phoneNumber, String message) {

        SmsManager sms = SmsManager.getDefault();
        sms.sendTextMessage(phoneNumber, null, message, null, null);
    }

}
