package com.example.enee499lmerged;

import static com.googlecode.javacv.cpp.opencv_core.IPL_DEPTH_8U;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.text.SimpleDateFormat;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.List;
import java.util.Locale;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import uk.ac.shef.wit.simmetrics.similaritymetrics.JaroWinkler;

import com.googlecode.javacv.cpp.opencv_core.IplImage;
import com.googlecode.tesseract.android.ResultIterator;
import com.googlecode.tesseract.android.TessBaseAPI.PageIteratorLevel;

import android.app.Fragment;
import android.content.ContentValues;
import android.content.Context;
import android.content.res.Configuration;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.hardware.Camera;
import android.hardware.Camera.AutoFocusCallback;
import android.hardware.Camera.Parameters;
import android.hardware.Camera.PictureCallback;
import android.hardware.Camera.Size;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.provider.MediaStore;
import android.provider.MediaStore.Images;
import android.provider.MediaStore.Images.Media;
import android.speech.tts.TextToSpeech;
import android.text.Html;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.ToggleButton;

public class AutoModeFragment extends Fragment{
	private Context mContext;
	private Camera mCamera;
	private ConcurrentLinkedQueue<String> sendQueue = new ConcurrentLinkedQueue<String>();
	private Handler handler = new Handler();
	private final SimpleDateFormat time = new SimpleDateFormat("hh_mm_ss", Locale.US);
	
	//Views
	private View rootView;
	private ImageView lastProcImage;
	private EditText searchQuery;
	private TextView lastReceived, lastSent, lastRead;
	private ToggleButton btToggle;
	private Button simulateCamera;
	
	private final JaroWinkler algo = new JaroWinkler();
	private final Pattern roomNumRegex = Pattern.compile("\\d+");
	private final Pattern recognizedTextRegex = Pattern.compile("[\\d+ ?\\d*]+");
	private AutoModeFragment fragmentContext;
	
	//Communication constants
	private final String TAKE_PICTURE = "TAKE PICTURE";
	private final String CONTINUE_NAVIGATION = "C";
	private final String STOP_NAVIGATION = "S";
	private final String SKIP_NEXT_DOOR = "K";

	public AutoModeFragment()
	{
		
	}
	
	public static AutoModeFragment newInstance()
	{
		return new AutoModeFragment();
	}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		rootView = inflater.inflate(R.layout.auto_fragment, container, false);
		mContext = rootView.getContext();
		fragmentContext = this;
		
		//Set up views
		btToggle = (ToggleButton) rootView.findViewById(R.id.buttonToggleBTComms);
		simulateCamera = (Button) rootView.findViewById(R.id.buttonSimCamRequest);
		lastReceived = (TextView) rootView.findViewById(R.id.textLastCommandReceived);
		lastSent = (TextView) rootView.findViewById(R.id.textLastCommandSent);
		lastRead = (TextView) rootView.findViewById(R.id.lastStringRead);
		searchQuery = (EditText) rootView.findViewById(R.id.roomSearchText);
		
		btToggle.setOnCheckedChangeListener(new OnCheckedChangeListener(){
			Thread worker;
			
			@Override
			public void onCheckedChanged(CompoundButton buttonView,
					boolean isChecked) {
				if(!isChecked)
				{
					worker.interrupt();
					while(worker.isAlive())
						;
					InitFragment.postToConsole("Communications closed.");
				}
				else
					worker = btThread(buttonView);
			}
			
		});
		
		lastProcImage = (ImageView) rootView.findViewById(R.id.imageLastProcessed);
		
		simulateCamera.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				autoTakeImage();
			}
		});
		
		return rootView;
	}
	
	private void autoTakeImage()
	{
		final PictureCallback mPicture = new PictureCallback() {

		    @Override
		    public void onPictureTaken(final byte[] data, final Camera camera) {
		    	
		    	handler.post(new Runnable(){

					@Override
					public void run() {
						camera.startPreview();

						Bitmap bitmap = BitmapFactory.decodeByteArray(data, 0, data.length);
						
						/*
						try {
							File dest = new File(Environment.getExternalStorageDirectory() + "/AUTO_MODE/" + time.format(new Date()) + ".jpg");
							dest.getParentFile().mkdirs();
							bitmap.compress(Bitmap.CompressFormat.JPEG, 95, new FileOutputStream(dest));
						} catch (FileNotFoundException e) {
							Log.i("enee499lmerged", "failed with error: " + e.getMessage());
						}
						*/
						
						IplImage openCVImg = ImagingInterfaces.performEdgeDetection(bitmap);
						
						bitmap.recycle();
						bitmap = Bitmap.createBitmap(openCVImg.width(), openCVImg.height(), Bitmap.Config.ARGB_8888);
						bitmap.copyPixelsFromBuffer(openCVImg.getByteBuffer());
						
						int w = bitmap.getWidth();
	            	    int h = bitmap.getHeight();
	            	    
	            	    Matrix mtx = new Matrix();
	            	    
	            	    if(fragmentContext.getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT)
	            	    	mtx.preRotate(90);

	            	    bitmap = Bitmap.createBitmap(bitmap, 0, 0, w, h, mtx, false);
	            	    bitmap = bitmap.copy(Bitmap.Config.ARGB_8888, true);
				    	lastProcImage.setImageBitmap(bitmap);
				    	
						
		            	StringBuilder result = new StringBuilder();
		            	StringBuilder resultHighConf = new StringBuilder();
		            	
		            	ManualModeFragment.runTesseractOCR(bitmap, result, resultHighConf);
		            	
		            	final String recognizedText = result.toString().trim();
		            	String recognizedTextHighConf = resultHighConf.toString().trim();
		            	final String searchText = searchQuery.getText().toString();
				    	float prob1 = algo.getSimilarity(recognizedText, searchText), prob2 = algo.getSimilarity(recognizedTextHighConf, searchText);
				    	
				    	if(searchText.length() == 0)
				    		prob1 = prob2 = 0;
				    	
				    	//lastRead.setText(Html.fromHtml(recognizedText));
				    	
		            	Matcher regexMatcher = roomNumRegex.matcher(searchText);
				    	Matcher recognizedMatcher = recognizedTextRegex.matcher(recognizedTextHighConf);
				    	
				    	if(recognizedMatcher.groupCount() > 0)
				    		recognizedTextHighConf = recognizedTextHighConf.replace(recognizedMatcher.group(0), recognizedMatcher.group(0).replace(" ", ""));
		            	
		            	if(prob1 > .9 || prob2 > .9 || (regexMatcher.matches() && 
		            			(recognizedTextHighConf.contains(regexMatcher.group()) || recognizedText.contains(regexMatcher.group()))
		            	)){
		            		sendQueue.add(STOP_NAVIGATION);
			            	ManualModeFragment.ttsEngine.speak("Found target room: " + recognizedTextHighConf, TextToSpeech.QUEUE_ADD, null);
		            		Log.i("STOP", "prob1: " + prob1 + ", prob2: " + prob2 + " strings: " + recognizedText + " , " + recognizedTextHighConf);
		            		//Toast.makeText(mContext, "STOP: prob1: " + prob1 + ", prob2: " + prob2 + " strings: " + recognizedText + " , " + recognizedTextHighConf, Toast.LENGTH_LONG).show();
		            	}
		            	else if(recognizedTextHighConf.length() == 0)
		            	{
		            		sendQueue.add(CONTINUE_NAVIGATION);
		            		Log.i("CONTINUE", "prob1: " + prob1 + ", prob2: " + prob2 + " strings: " + recognizedText + " , " + recognizedTextHighConf);
		            		//Toast.makeText(mContext, "CONTINUE: prob1: " + prob1 + ", prob2: " + prob2 + " strings: " + recognizedText + " , " + recognizedTextHighConf, Toast.LENGTH_LONG).show();
		            	}
		            	else
		            	{
		            		sendQueue.add(SKIP_NEXT_DOOR);
		            		ManualModeFragment.ttsEngine.speak("Now passing: " + recognizedTextHighConf, TextToSpeech.QUEUE_ADD, null);
		            		Log.i("SKIP DOOR", "prob1: " + prob1 + ", prob2: " + prob2 + " strings: " + recognizedText + " , " + recognizedTextHighConf);
		            		//Toast.makeText(mContext, "SKIP DOOR: prob1: " + prob1 + ", prob2: " + prob2 + " strings: " + recognizedText + " , " + recognizedTextHighConf, Toast.LENGTH_LONG).show();
		            	}
		            	
					}
		    	});				    	
		    }
		};
		
		mCamera = MainActivity.mCamera;
		SurfaceView surfaceView = (SurfaceView)rootView.findViewById(R.id.surfaceView1);

		Parameters camParams = mCamera.getParameters();
		Size prevSize = getBestPreviewSize(surfaceView.getWidth(), surfaceView.getHeight(), camParams);
		Size imgSize = getBestImgSize(camParams.getSupportedPictureSizes());
		
		camParams.setPictureSize(imgSize.width, imgSize.height);
		camParams.setPreviewSize(prevSize.width, prevSize.height);
		camParams.setFlashMode(Parameters.FLASH_MODE_AUTO);
		camParams.setFocusMode(Parameters.FOCUS_MODE_AUTO);
		
		mCamera.setParameters(camParams);
		final SurfaceHolder surfaceHolder = surfaceView.getHolder();
		try {
    	    if(fragmentContext.getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT)
    	    	mCamera.setDisplayOrientation(90);
    	    else
    	    	mCamera.setDisplayOrientation(0);
    	    
    	    
    	    mCamera.setPreviewDisplay(surfaceHolder);
			mCamera.startPreview();     
			
			
			mCamera.cancelAutoFocus();
			Thread.sleep(1250);
    	    mCamera.autoFocus(new AutoFocusCallback(){

				@Override
				public void onAutoFocus(boolean success, Camera camera) {
					if(success)
					{
						mCamera.takePicture(null, null, mPicture);
					}
				}
    	    });

		} catch (IOException e) {
			e.printStackTrace();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
	}
	
	private Thread btThread(CompoundButton buttonView) {
		if(InitFragment.socket == null || !InitFragment.socket.isConnected())
		{
			buttonView.setChecked(false);
			Toast.makeText(mContext, "Connect failed...", Toast.LENGTH_SHORT).show();
			InitFragment.postToConsole("Communcation opening failed.");
			return null;
		}

		Thread worker = new Thread(new Runnable()
        {		
    		int readBufferPosition = 0;
    		byte[] readBuffer = new byte[1024];
    		InputStream inStream;
    		OutputStream outStream;
    		String toSend;
        	
            public void run()
            {
				try
				{
					inStream = InitFragment.socket.getInputStream();
					outStream = InitFragment.socket.getOutputStream();
					InitFragment.postToConsole("Communications opened.");
					outStream.write("O".getBytes());
					InitFragment.postToConsole("O");
				}
				catch (Exception e)
				{
					Toast.makeText(mContext, "Connect failed...", Toast.LENGTH_SHORT).show();
					return;
				}
				
            	
               while(!Thread.currentThread().isInterrupted())
               {
            	   if(inStream == null || outStream == null)
            	   {
            		   InitFragment.postToConsole("BT not initialized.");
            		   return;
            	   }
            	   
            	   try
            	   {
                	   int bytesAvailable = inStream.available();
                       if(bytesAvailable > 0)
                       {
                           byte[] packetBytes = new byte[bytesAvailable];
                           inStream.read(packetBytes);
                           
                           for(int i=0;i<bytesAvailable;i++)
                           {
                               byte b = packetBytes[i];
                               if(b == '\n' || readBufferPosition >= 1023)
                               {
                                   byte[] encodedBytes = new byte[readBufferPosition];
                                   System.arraycopy(readBuffer, 0, encodedBytes, 0, encodedBytes.length);
                                   final String data = new String(encodedBytes, "US-ASCII");
                                   readBufferPosition = 0;
                                   final String timeStamp = time.format(new Date());
                                   InitFragment.postToConsole("Received @ " + timeStamp + ": " + data + "\n");
                                   
                                   if(data.startsWith(TAKE_PICTURE))
                                	   autoTakeImage();
                                   
                                   postToLastConsole(true, timeStamp + ": " + data);
                               }
                               else
                               {
                                   readBuffer[readBufferPosition++] = b;
                               }
                           }
                       }
                       if(!sendQueue.isEmpty() && (toSend = sendQueue.poll()) != null)
                       {
                    	   outStream.write(toSend.getBytes());
                    	   postToLastConsole(false, toSend);
                       }
                      
            	   } catch(final Exception e)
            	   {
            		   InitFragment.postToConsole("Reading message failed with error: " + e.getMessage());
            	   }

               }
            }
        });
		worker.start();
		return worker;
	}
	
	private Camera.Size getBestImgSize(List<Camera.Size> sizes)
	{
		return Collections.max(sizes, new Comparator<Size>(){

			@Override
			public int compare(Size arg0, Size arg1) {
				int size0 = arg0.height * arg0.width;
				int size1 = arg1.height * arg1.width;
				
				if(size0 == size1)
					return 0;
				
				return size0 > size1 ? 1 : -1;
			}
			
		});
	}
	
	private Camera.Size getBestPreviewSize(int width, int height, Camera.Parameters parameters){
        Size bestSize = null;
        List<Camera.Size> sizeList = parameters.getSupportedPreviewSizes();

        bestSize = sizeList.get(0);

        for(int i = 1; i < sizeList.size(); i++){
         if((sizeList.get(i).width * sizeList.get(i).height) >
           (bestSize.width * bestSize.height)){
          bestSize = sizeList.get(i);
         }
        }

        return bestSize;
     }
	
	private void postToLastConsole(final boolean received, final String text)
	{
		fragmentContext.getActivity().runOnUiThread(new Runnable(){

			@Override
			public void run() {
				if(received)
					fragmentContext.lastReceived.setText(text);
				else
					fragmentContext.lastSent.setText(text);
			}
			
		});
	}

}
