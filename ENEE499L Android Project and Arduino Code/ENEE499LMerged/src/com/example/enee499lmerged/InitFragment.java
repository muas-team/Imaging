package com.example.enee499lmerged;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;
import android.hardware.Camera;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.preference.PreferenceManager;
import android.text.Html;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

//This fragment will show BT/API Information
public class InitFragment extends android.app.Fragment{
	
	private BluetoothAdapter mBluetoothAdapter;
	private final static Handler handler = new Handler();
	private TextView btStatus, btConnectStatus, btSyncStatus;
	private View rootView;
	private static TextView consoleLog;
	private static ScrollView txtScroll;
	private static InitFragment mContext;

	
	public static BluetoothSocket socket;
	
	public InitFragment()
	{
		
	}
	
	public static InitFragment newInstance()
	{
		InitFragment fragment = new InitFragment();
		return fragment;
	}
	
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		mContext = this;
		rootView = inflater.inflate(R.layout.init_fragment, container, false);
		
		initBT();
		initAPI();
		initCamera();

		consoleLog = (TextView) rootView.findViewById(R.id.consoleView);
		txtScroll = (ScrollView) rootView.findViewById(R.id.scrollTxt);
		postToConsole("Text will appear here.\n");

		return rootView;
	}
	
	public static void postToConsole(final String text)
	{
		mContext.getActivity().runOnUiThread(new Runnable()
        {
            public void run()
            {
                consoleLog.setText(consoleLog.getText() + text + "\n");
                txtScroll.fullScroll(View.FOCUS_DOWN);
            }
        });
	}

	private void initCamera() {
		TextView cameraStatus = (TextView) rootView.findViewById(R.id.textCameraStatus);
		
		if(this.getActivity().getPackageManager().hasSystemFeature(PackageManager.FEATURE_CAMERA))
		{
			MainActivity.cameraAvailable = MainActivity.safeCameraOpen();
		}
		
		if(MainActivity.cameraAvailable)
			cameraStatus.setText(Html.fromHtml("Camera Status: <font color=\"olive\">OK</font>"));
		else
			cameraStatus.setText(Html.fromHtml("Camera Status: <font color=\"red\">No camera detected</font>"));
	}

	private void initAPI() {
		Context activityContext = this.getActivity().getApplicationContext();
		boolean installStatus = PreferenceManager.getDefaultSharedPreferences(activityContext).getBoolean("installed", false);
		if (!installStatus) {
          
    		AssetManager assets = this.getActivity().getAssets();
    		InputStream stream;
    		OutputStream output;
    		try
    		{
    			File tessData = new File(this.getActivity().getFilesDir() + "/tesseract/tessdata/");
    			tessData.mkdirs();
    			
    			for(String fileName : assets.list(""))
    			{
    				if(!fileName.startsWith("eng"))
    					continue;
    				
    			    stream = assets.open(fileName);
    			    
    				output = new BufferedOutputStream(new FileOutputStream(this.getActivity().getFilesDir() + "/tesseract/tessdata/" + fileName));
    				byte data[] = new byte[1024];
    			    int count;

    			    while((count = stream.read(data)) != -1)
    			    {
    			        output.write(data, 0, count);
    			    }

    			    output.flush();
    			    output.close();
    			    stream.close();

    			    stream = null;
    			    output = null;
    			}
    			installStatus = true;
    			PreferenceManager.getDefaultSharedPreferences(activityContext).edit().putBoolean("installed", true).commit();
    		} catch(Exception e)
    		{
    			Log.d("APIERR", e.getMessage());
    		}
        }
		TextView apiStatus = (TextView) rootView.findViewById(R.id.textAPIStatus);
		
		if(!installStatus)
			apiStatus.setText(Html.fromHtml("API Status: <font color=\"red\">Failure</font>"));
		else
			apiStatus.setText(Html.fromHtml("API Status: <font color=\"olive\">OK</font>"));
	}

	private void initBT() {
		mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		btStatus = (TextView) rootView.findViewById(R.id.textBTStatus);
		btSyncStatus = (TextView) rootView.findViewById(R.id.textBTSyncStatus);
		btConnectStatus = (TextView) rootView.findViewById(R.id.textBTConnectStatus);

		if(mBluetoothAdapter == null)
			btStatus.setText(Html.fromHtml("Bluetooth Status: <font color=\"red\">No Adapter Found</font>"));
		else
		{
			setBTStatus(mBluetoothAdapter.getState());
			btStatus.setOnClickListener(new OnClickListener(){
	
				@Override
				public void onClick(View v) {
					if(!mBluetoothAdapter.isEnabled())
					{
					   Intent enableBluetooth = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
					   startActivityForResult(enableBluetooth, 0);
					}
				}
				
			});
			
			btConnectStatus.setOnClickListener(new OnClickListener(){

				@Override
				public void onClick(final View v) {
					try
					{
						if(mBluetoothAdapter.getBondedDevices().size() == 0)
						{
							btSyncStatus.setText(Html.fromHtml("Synced with: <font color=\"red\">" + "No device found" + "</font>"));
					        btConnectStatus.setText(Html.fromHtml("Connection Status: <font color=\"red\">Error</font>"));
					        return;
						}
						
						BluetoothDevice device = mBluetoothAdapter.getBondedDevices().iterator().next();
						UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb"); //Standard SerialPortService ID
	
						postToConsole("Attemping to connect to device: " + device.getName() + " with address: " + device.getAddress());
						
				        socket = device.createRfcommSocketToServiceRecord(uuid);
				        socket.connect();
				        
						postToConsole("Socket creation sucessful. Enable communication from Auto Mode page.");
				        btConnectStatus.setText(Html.fromHtml("Connection Status: <font color=\"olive\">Connected</font>"));
				        btSyncStatus.setText(Html.fromHtml("Connection Status: <font color=\"olive\">" + device.getName() +"</font>"));
					}
					catch (Exception e)
					{
						btConnectStatus.setText(Html.fromHtml("Connection Status: <font color=\"red\">Failed</font>"));
						Log.i("Error", e.getMessage());
					}
											
				}
			});
			
			IntentFilter filter = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
		    this.getActivity().registerReceiver(btStateReceiver, filter);
		}
	}
		
	private final BroadcastReceiver btStateReceiver = new BroadcastReceiver() {
	    @Override
	    public void onReceive(Context context, Intent intent) {
	        final String action = intent.getAction();

	        if (action.equals(BluetoothAdapter.ACTION_STATE_CHANGED)) {
	            final int state = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE,
	                                                 BluetoothAdapter.ERROR);
	            setBTStatus(state);
	        }
	    }
	};
	
	private void setBTStatus(int state)
	{
		 switch (state) {
		 case BluetoothAdapter.STATE_CONNECTED:
			btStatus.setText(Html.fromHtml("Bluetooth Status: <font color=\"olive\">Connected</font>"));
			 				
			try
			{
				BluetoothDevice device = mBluetoothAdapter.getBondedDevices().iterator().next();
				btSyncStatus.setText(Html.fromHtml("Synced with: <font color=\"red\">" + device.getName() + "</font>"));
		        btConnectStatus.setText(Html.fromHtml("Connection Status: <font color=\"red\">Tap to connect</font>"));
			}
			catch (final Exception e)
			{
				btSyncStatus.setText(Html.fromHtml("Synced with: <font color=\"red\">" + "No device found?" + "</font>"));
		        btConnectStatus.setText(Html.fromHtml("Connection Status: <font color=\"red\">Error</font>"));
			}

			 break;
         case BluetoothAdapter.STATE_OFF:
         	btStatus.setText(Html.fromHtml("Bluetooth Status: <font color=\"red\">Off</font>"));
         	btSyncStatus.setText(Html.fromHtml("Synced with: <font color=\"red\">None</font>"));
         	btConnectStatus.setText(Html.fromHtml("Connection Status: <font color=\"red\">N/A</font>"));
            break;
         case BluetoothAdapter.STATE_TURNING_OFF:
         	btStatus.setText(Html.fromHtml("Bluetooth Status: <font color=\"red\">Turning off..</font>"));
             break;
         case BluetoothAdapter.STATE_ON:
         	btStatus.setText(Html.fromHtml("Bluetooth Status: <font color=\"olive\">On</font>"));
         	btSyncStatus.setText(Html.fromHtml("Synced with: <font color=\"red\">None</font>"));
         	btConnectStatus.setText(Html.fromHtml("Connection Status: <font color=\"red\">N/A</font>"));
            break;
         case BluetoothAdapter.STATE_TURNING_ON:
         	btStatus.setText(Html.fromHtml("Bluetooth Status: <font color=\"olive\">Turning on..</font>"));
             break;
         }
	}
	
	@Override
	public void onDestroy() {
	    super.onDestroy();

	    // Unregister broadcast listeners
	    this.getActivity().unregisterReceiver(btStateReceiver);
	}
	
	
}
