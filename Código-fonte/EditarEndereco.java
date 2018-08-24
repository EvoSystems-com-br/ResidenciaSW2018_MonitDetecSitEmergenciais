package com.example.gabri.tccv1;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class EditarEndereco extends AppCompatActivity {

    EditText et_endereco;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_editar_endereco);

        et_endereco = findViewById(R.id.cadastro_endereco_casa);

        Button b_cadastro_endereco = (Button) findViewById(R.id.b_cadastro_endereco); // Informar estado
        b_cadastro_endereco.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                //SharedPreferences sharedPref = getPreferences(MODE_PRIVATE);
                SharedPreferences sharedPreferences = getSharedPreferences("endereco_casa", Context.MODE_PRIVATE);
                SharedPreferences.Editor editor = sharedPreferences.edit();
                editor.putString("endereco_casa",et_endereco.getText().toString());
                editor.apply();

                Toast.makeText(v.getContext(), "Endereço atualizado!", Toast.LENGTH_SHORT).show();
            }
        });
    }
}
