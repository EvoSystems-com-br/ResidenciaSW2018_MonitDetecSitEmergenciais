package com.example.gabri.tccv1;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class EditarContato extends AppCompatActivity {

    EditText et_nome, et_telefone;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_editar_contato);

        et_nome = findViewById(R.id.nome_cadastro);
        et_telefone = findViewById(R.id.telefone_cadastro);


        Button b_cadastro = (Button) findViewById(R.id.b_cadastro); // Informar estado
        b_cadastro.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                //SharedPreferences sharedPref = getPreferences(MODE_PRIVATE);
                SharedPreferences sharedPreferences = getSharedPreferences("nome_contato", Context.MODE_PRIVATE);
                SharedPreferences.Editor editor = sharedPreferences.edit();
                editor.putString("nome_contato",et_nome.getText().toString());
                editor.commit();


                sharedPreferences = getSharedPreferences("telefone_contato", Context.MODE_PRIVATE);
                editor = sharedPreferences.edit();
                editor.putString("telefone_contato",et_telefone.getText().toString());
                editor.commit();

                Toast.makeText(v.getContext(), "Contato atualizado!", Toast.LENGTH_SHORT).show();
            }
        });

    }

}
