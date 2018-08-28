package com.example.gabri.tccv1;

import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.View;
import android.widget.Button;



public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button b_estado = (Button) findViewById(R.id.b_estado); // Informar estado
        b_estado.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent i = new Intent(v.getContext(), EstadoPaciente.class);
                startActivity(i);// Vai para Activity EstadoPaciente
            }
        });

        Button b_parametros = (Button) findViewById(R.id.b_parametros); // Parâmetros de Segurança
        b_parametros.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent i = new Intent(v.getContext(), ParametrosSeguranca.class);
                startActivity(i);// Vai para Activity ParâmetrosSeguranca
            }
        });
    }
}
