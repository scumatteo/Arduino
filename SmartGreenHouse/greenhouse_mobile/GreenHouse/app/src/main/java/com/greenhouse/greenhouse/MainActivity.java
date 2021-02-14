package com.greenhouse.greenhouse;

import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.nio.charset.*;
import java.util.Timer;
import java.util.UUID;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {
    private final Handler handler = new Handler();
    private boolean connession_state = false;
    private Timer timer = new Timer(false);
    private TimerTask timerTask;

    private boolean test = false;

    //Bluetooth Variables
    private UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private BluetoothAdapter mBluetoothAdapter = null;
    private BluetoothSocket mmSocket = null;
    private BluetoothDevice mmDevice = null;
    protected OutputStream outStream;
    protected InputStream inputStream;

    //Gui Variables
    private EditText umidityText;
    private SeekBar seekBar;
    private EditText flowText;
    private TextView stateLabel;

    //Modal variables
    private double umidity;
    private double flow;
    private boolean manual = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        umidityText = (EditText)findViewById(R.id.umidity);
        seekBar = (SeekBar)findViewById(R.id.seekBar);
        flowText = (EditText)findViewById(R.id.inputP);
        stateLabel = (TextView)findViewById(R.id.stateView);



        gui();
        while(!connession_state){
            connession_state = connession();
        }
        loop();
    }

    private void gui() {
        umidityText.setEnabled(false);
        seekBar.setEnabled(false);
        flowText.setEnabled(false);
        stateLabel.setEnabled(false);
        stateLabel.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(stateLabel.getText() == "AUTO"){
                    manual = true;
                    stateLabel.setText("MANUAL");
                    umidityText.setEnabled(true);
                    seekBar.setEnabled(true);
                    flowText.setEnabled(true);
                }else{
                    manual = false;
                    stateLabel.setText("AUTO");
                    umidityText.setEnabled(false);
                    seekBar.setEnabled(false);
                    flowText.setEnabled(false);
                }
            }
        });
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                flowText.setText(String.valueOf(progress));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
        flowText.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {

            }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                seekBar.setProgress(Integer.parseInt(s.toString()));
            }

            @Override
            public void afterTextChanged(Editable s) {
            }
        });
    }

    private boolean writeMessageBluetooth(String message) {
        boolean success = false;
        if (outStream == null)
        {
            return false;
        }
        byte[] msgBuffer = message.getBytes();
        try
        {
            outStream.write(msgBuffer);
            Log.d("Bluetooth write message", msgBuffer.toString());
            success = true;
        }
        catch (IOException e)
        {
            Toast.makeText(MainActivity.this, "Messaggio non Inviato", Toast.LENGTH_SHORT).show();
        }
        return success;
    }

    private String readMessageBluetooth() {
        String msg_r = "null";
        if (inputStream == null)
        {
            return "null";
        }
        try
        {
            int bytes = inputStream.available();
            if(bytes>0){
                byte[] msg = new byte[bytes];
                inputStream.read(msg);
                Log.d("Bluetooth read message", msg.toString());
                msg_r = new String(msg, Charset.forName("UTF-8"));
            }else{
                return "null";
            }
        }
        catch (IOException e)
        {
            Toast.makeText(MainActivity.this, "Messaggio non letto", Toast.LENGTH_SHORT).show();
            return "null";
        }
        return msg_r;
    }

    protected boolean connession() {
        boolean success = false;
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        //controlla se il devices è supportato
        if (mBluetoothAdapter == null) {
            // IL BLUETOOTH NON E' SUPPORTATO
            Toast.makeText(MainActivity.this, "BlueTooth non supportato", Toast.LENGTH_LONG).show();
        } else {
            //controlla che sia abilitato il device
            if (!mBluetoothAdapter.isEnabled()) {
                //  NON E' ABILITATO IL BLUETOOTH
                Toast.makeText(MainActivity.this, "BlueTooth non abilitato", Toast.LENGTH_LONG).show();
            } else {
                //  IL BLUETOOTH E' ABILITATO
                mmDevice = mBluetoothAdapter.getRemoteDevice("");
                //MAC address del bluetooth di arduino
                try {
                    mmSocket = mmDevice.createRfcommSocketToServiceRecord(uuid);
                } catch (IOException e) { }
                try {
                    // CONNETTE IL DISPOSITIVO TRAMITE IL SOCKET mmSocket
                    mmSocket.connect();
                    inputStream = mmSocket.getInputStream();
                    outStream = mmSocket.getOutputStream();
                    Toast.makeText(MainActivity.this, "ON", Toast.LENGTH_SHORT).show();//bluetooth è connesso
                    success = true;
                } catch (IOException closeException) {
                    success = false;
                    try {
                        //TENTA DI CHIUDERE IL SOCKET
                        mmSocket.close();
                        outStream.close();
                        inputStream.close();
                    } catch (IOException ceXC) { }
                    Toast.makeText(MainActivity.this, "connessione non riuscita", Toast.LENGTH_SHORT).show();
                }
            }   //CHIUDE l'else di isEnabled
        }//CHIUDE l'else di mBluetoothAdapter == nul

        return success;
    }

    protected void loop() {
        if(!connession_state){
            Toast.makeText(MainActivity.this,"Connessione non riuscita, impossibile comunicare con arduino", Toast.LENGTH_LONG).show();
            return;
        }
        stateLabel.setEnabled(true);
        timerTask = new TimerTask() {
            @Override
            public void run() {
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        String msg = readMessageBluetooth();
                        umidity = Integer.parseInt(msg);
                        umidityText.setText(String.valueOf(umidity)+"%");
                        writeMessageBluetooth(flowText.getText().toString());
                    }
                });
            }
        };
        timer.schedule(timerTask, 10000); // 1000 = 1 second
    }
}
