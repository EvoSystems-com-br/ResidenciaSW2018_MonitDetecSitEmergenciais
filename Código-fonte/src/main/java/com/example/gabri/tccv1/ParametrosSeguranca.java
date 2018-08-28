package com.example.gabri.tccv1;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.w3c.dom.Text;

public class ParametrosSeguranca extends AppCompatActivity {

    TextView tv_nome, tv_telefone, tv_endereco;
    String str_nome,str_telefone,str_endereco;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_parametros_seguranca);

        tv_nome = (TextView)findViewById(R.id.nome_contato);
        tv_telefone = (TextView)findViewById(R.id.telefone_contato);
        tv_endereco = (TextView)findViewById(R.id.endereco_casa);

        SharedPreferences sharedPref = getSharedPreferences("nome_contato", Context.MODE_PRIVATE);
        str_nome = sharedPref.getString("nome_contato",null);

        sharedPref = getSharedPreferences("telefone_contato", Context.MODE_PRIVATE);
        str_telefone = sharedPref.getString("telefone_contato",null);

        sharedPref = getSharedPreferences("endereco_casa", Context.MODE_PRIVATE);
        str_endereco = sharedPref.getString("endereco_casa",null);

        if(str_nome == null){
            tv_nome.setText("Contato não cadastrado");
            tv_telefone.setText("");
        }else{
            tv_nome.setText(str_nome);
            tv_telefone.setText(str_telefone);
        }

        if(str_endereco == null){
            tv_endereco.setText("Endereço não cadastrado");
        }else{
            tv_endereco.setText(str_endereco);
        }



        Button b_editar_contato = (Button) findViewById(R.id.b_editar_contato); // Informar estado
        b_editar_contato.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent i = new Intent(v.getContext(), EditarContato.class);
                startActivity(i);// Vai para Activity EstadoPaciente
            }
        });

        Button b_editar_endereco = (Button) findViewById(R.id.b_editar_endereco); // Parâmetros de Segurança
        b_editar_endereco.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Intent i = new Intent(v.getContext(), EditarEndereco.class);
                startActivity(i);// Vai para Activity ParâmetrosSeguranca
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        tv_nome = (TextView)findViewById(R.id.nome_contato);
        tv_telefone = (TextView)findViewById(R.id.telefone_contato);
        tv_endereco = (TextView)findViewById(R.id.endereco_casa);

        SharedPreferences sharedPref = getSharedPreferences("nome_contato", Context.MODE_PRIVATE);
        str_nome = sharedPref.getString("nome_contato",null);

        sharedPref = getSharedPreferences("telefone_contato", Context.MODE_PRIVATE);
        str_telefone = sharedPref.getString("telefone_contato",null);

        sharedPref = getSharedPreferences("endereco_casa", Context.MODE_PRIVATE);
        str_endereco = sharedPref.getString("endereco_casa",null);

        if(str_nome == null){
            tv_nome.setText("Contato não cadastrado");
            tv_telefone.setText("");
        }else{
            tv_nome.setText(str_nome);
            tv_telefone.setText(str_telefone);
        }

        if(str_endereco == null){
            tv_endereco.setText("Endereço não cadastrado");
        }else{
            tv_endereco.setText(str_endereco);
        }


    }
}