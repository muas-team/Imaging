package com.example.enee499lmerged;

import static com.googlecode.javacv.cpp.opencv_core.IPL_DEPTH_8U;

import java.io.FileNotFoundException;
import java.io.IOException;

import com.googlecode.javacv.cpp.opencv_core.IplImage;
import com.googlecode.leptonica.android.Box;
import com.googlecode.leptonica.android.Pixa;
import com.googlecode.tesseract.android.ResultIterator;
import com.googlecode.tesseract.android.TessBaseAPI;
import com.googlecode.tesseract.android.TessBaseAPI.PageIteratorLevel;

import android.app.Activity;
import android.app.Fragment;
import android.app.ProgressDialog;
import android.content.ActivityNotFoundException;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.Matrix;
import android.media.ExifInterface;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.speech.tts.TextToSpeech;
import android.text.Html;
import android.text.Spanned;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class ManualModeFragment extends Fragment{

	private static final int CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE = 100;
	private static final int SELECT_PHOTO = 101;
	private static final int REQUEST_CODE_CROP_IMAGE = 102;
	private Activity mContext;
	private View rootView;
	
	public static TessBaseAPI baseApi;
	public static final int MEDIA_TYPE_IMAGE = 1;
	public static final int MEDIA_TYPE_VIDEO = 2;
	public static TextToSpeech ttsEngine;
	private static Uri fileUri;
	
	public ManualModeFragment()
	{
		
	}
	
	public static ManualModeFragment newInstance()
	{
		return new ManualModeFragment();
	}
	
	@Override
	public View onCreateView(LayoutInflater inflater, ViewGroup container,
			Bundle savedInstanceState) {
		
		rootView = inflater.inflate(R.layout.manual_fragment, container, false);
		
		ttsEngine = new TextToSpeech(this.getActivity(), null);
		baseApi = new TessBaseAPI();
    	baseApi.init(this.getActivity().getFilesDir() + "/tesseract", "eng+eng1");
		baseApi.setVariable("tessedit_char_whitelist", "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.! ");
		baseApi.setVariable("save_best_choices", "T");

    	mContext = this.getActivity();
		Button snapShotButton = (Button) rootView.findViewById(R.id.snapshotButton);
		snapShotButton.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View v) {
				ttsEngine.stop();
				 // create Intent to take a picture and return control to the calling application
			    Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);

			    fileUri = ImagingInterfaces.getOutputMediaFileUri(MEDIA_TYPE_IMAGE); // create a file to save the image
			    intent.putExtra(MediaStore.EXTRA_OUTPUT, fileUri); // set the image file name

			    // start the image capture Intent
			    startActivityForResult(intent, CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE);
			}
			
		});
		
		Button selectPhotoButton = (Button) rootView.findViewById(R.id.selectPhotoButton);
		selectPhotoButton.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View arg0) {
				ttsEngine.stop();
				Intent photoPickerIntent = new Intent(Intent.ACTION_PICK);
				photoPickerIntent.setType("image/*");
				startActivityForResult(photoPickerIntent, SELECT_PHOTO);  
			}
			
		});
		
		
		return rootView;
	}
	
	@Override
	public void onActivityResult(int requestCode, int resultCode, final Intent data) {		
	    if ((requestCode == CAPTURE_IMAGE_ACTIVITY_REQUEST_CODE || requestCode == SELECT_PHOTO) 
	    		&& resultCode == Activity.RESULT_OK) {	
	    	
	    		if(requestCode == SELECT_PHOTO)
	    			fileUri = data.getData();
	    		
	    		try
	    		{
					Bitmap bmpCopy;
					try {
						bmpCopy = MediaStore.Images.Media.getBitmap(mContext.getContentResolver(), fileUri);
						//bmpCopy = ImagingInterfaces.changeBitmapContrastBrightness(bmpCopy, (float) 1.5, -10);
						CheckBox edgeDetection = (CheckBox) rootView.findViewById(R.id.checkboxEdge);
						if(edgeDetection.isChecked())
						{
							bmpCopy = bmpCopy.copy(Bitmap.Config.ARGB_8888, true);
							IplImage openCVImg = ImagingInterfaces.performEdgeDetection(bmpCopy);
					        
							bmpCopy.recycle();
							bmpCopy = Bitmap.createBitmap(openCVImg.width(), openCVImg.height(), Bitmap.Config.ARGB_8888);
							bmpCopy.copyPixelsFromBuffer(openCVImg.getByteBuffer());
						}
						
						final Bitmap bmp = bmpCopy;
						final ProgressDialog dialog = new ProgressDialog(mContext);
			            dialog.setMessage("Now performing OCR, please wait");
			            dialog.show();
			            
			            Thread ocrThread = new Thread(new Runnable(){
			            	Bitmap localBmp = bmp;
							@Override
							public void run() {
								try {

					            	final ImageView iv = (ImageView) mContext.findViewById(R.id.imageView1);
					            	
					            	ExifInterface exif = new ExifInterface(getRealPathFromURI(fileUri));
					            	int exifOrientation = exif.getAttributeInt(
					            	        ExifInterface.TAG_ORIENTATION,
					            	        ExifInterface.ORIENTATION_NORMAL);
					            	int rotate = 0;

					            	switch (exifOrientation) {
					            	case ExifInterface.ORIENTATION_ROTATE_90:
					            	    rotate = 90;
					            	    break;
					            	case ExifInterface.ORIENTATION_ROTATE_180:
					            	    rotate = 180;
					            	    break;
					            	case ExifInterface.ORIENTATION_ROTATE_270:
					            	    rotate = 270;
					            	    break;
					            	}
					            	
					            	if (rotate != 0) {
					            	    int w = localBmp.getWidth();
					            	    int h = localBmp.getHeight();

					            	    // Setting pre rotate
					            	    Matrix mtx = new Matrix();
					            	    mtx.preRotate(rotate);

					            	    // Rotating Bitmap & convert to ARGB_8888, required by tess
					            	    localBmp = Bitmap.createBitmap(localBmp, 0, 0, w, h, mtx, false);
					            	}
					            	
					            	StringBuilder result = new StringBuilder();
					            	StringBuilder resultHighConf = new StringBuilder();
					            	
					            	runTesseractOCR(localBmp, result, resultHighConf);
					            	
					            	final String recognizedText = result.toString().trim();
					            	final String recognizedTextHighConf = resultHighConf.toString().trim();
					            	//baseApi.end();
					            	final TextView tv = (TextView) mContext.findViewById(R.id.OCRResults);
					            	
					            	mContext.runOnUiThread(new Runnable(){
						                @Override
						                public void run() {
						                	Spanned html = Html.fromHtml(recognizedText);
						                	tv.setText(html);
							            	iv.setImageBitmap(bmp);
							            	dialog.dismiss();
							            	ttsEngine.speak(recognizedTextHighConf, TextToSpeech.QUEUE_ADD, null);
						                }                   
						            }); 

								} catch (Exception e)
								{
									Log.d("ERROR", e.toString());
									mContext.runOnUiThread(new Runnable(){
						                @Override
						                public void run() {
						                    dialog.dismiss();
						                }                   
						            }); 
								}
							}
			            	
			            });
						
			            ocrThread.start();
		    			
					} catch (FileNotFoundException e) {
					} catch (IOException e) {
					}

	    			
	    		}
	    		catch(ActivityNotFoundException e)
	    		{
	    			Toast.makeText(mContext, "failed crop with error: " + e.getMessage(), Toast.LENGTH_LONG).show();
	    		}
	    }
	}
	
	public static void runTesseractOCR(Bitmap bmp,
			StringBuilder result, StringBuilder resultHighConf) {
		
		baseApi.setImage(bmp);
		baseApi.getUTF8Text();
		ResultIterator results = baseApi.getResultIterator();
		Pixa regions = baseApi.getWords();
		results.begin();
		int level = PageIteratorLevel.RIL_WORD, ctr = 0;
		
		if(results != null)
		{
			do
			{
				String word = results.getUTF8Text(level);
				Box box = regions.getBox(ctr++);
				
				
				if(box != null)
					System.out.println("Size: " + box.getHeight() + "x" + box.getWidth() + " , \"" + word + "\"");
				else
					System.out.println("Size: " + "???" + "x" + "???" + " , \"" + word + "\"");
				
				
				if(result.length() == 0 && word != null && (word.startsWith(".") || word.startsWith("o")))
					word = word.substring(1);
				
				float confidence = results.confidence(level);
				
				if(box != null && box.getHeight() < 50 && box.getWidth() < 50)
					confidence = 0;
				
				Log.i(word, confidence + "");
				
				if(confidence < 40)
					result.append("<font color=\"red\"><b>" + word + " </b></font>");
				else
				{
					result.append(word + " ");
					resultHighConf.append(word + " ");
				}
				
				
			} while (results.next(level));
			
		}
	}
	
	private String getRealPathFromURI(Uri contentURI) {
	    String result;
	    Cursor cursor = mContext.getContentResolver().query(contentURI, null, null, null, null);
	    if (cursor == null) { // Source is Dropbox or other similar local file path
	        result = contentURI.getPath();
	    } else { 
	        cursor.moveToFirst(); 
	        int idx = cursor.getColumnIndex(MediaStore.Images.ImageColumns.DATA); 
	        result = cursor.getString(idx);
	        cursor.close();
	    }
	    return result;
	}
	
	@Override
	public void onDestroy()
	{
		try
		{
			baseApi.end();
			ttsEngine.shutdown();
		}
		catch(Exception e)
		{}
		super.onDestroy();
	}
}
