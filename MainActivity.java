package com.example.iotesp32firebase;

import android.graphics.Color;
import android.media.Ringtone;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.Bundle;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.ToggleButton;
import android.graphics.Color;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    String valueJarak;
    String valueLdr;
    TextView jarak;
    TextView ldr;
    Button status;
    DatabaseReference dref;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ldr = (TextView) findViewById(R.id.ldr);
        jarak = (TextView) findViewById(R.id.jarak);
        status = (Button) findViewById(R.id.status);


        dref = FirebaseDatabase.getInstance().getReference();
        dref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {

                valueLdr = dataSnapshot.child("Node1/ldr").getValue().toString();
                ldr.setText(valueLdr);

                valueJarak = dataSnapshot.child("Node1/distance").getValue().toString();
                jarak.setText(valueJarak);

                if(Integer.parseInt(valueJarak) <= 50){
                    status.setBackgroundColor(Color.RED);
                    status.setText("Bahaya");
                    status.setTextColor(Color.WHITE);

                    try {
                        Uri notification = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
                        Ringtone r = RingtoneManager.getRingtone(getApplicationContext(), notification);
                        r.play();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }else{
                    status.setBackgroundColor(Color.GREEN);
                    status.setText("Aman");
                    status.setTextColor(Color.BLACK);
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

    }
}
