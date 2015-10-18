package com.example.enee499lmerged;

import static com.googlecode.javacpp.Loader.sizeof;
import static com.googlecode.javacv.cpp.opencv_core.CV_32F;
import static com.googlecode.javacv.cpp.opencv_core.CV_FILLED;
import static com.googlecode.javacv.cpp.opencv_core.CV_RGB;
import static com.googlecode.javacv.cpp.opencv_core.CV_WHOLE_SEQ;
import static com.googlecode.javacv.cpp.opencv_core.cvCopy;
import static com.googlecode.javacv.cpp.opencv_core.cvCreateImage;
import static com.googlecode.javacv.cpp.opencv_core.cvCreateMat;
import static com.googlecode.javacv.cpp.opencv_core.cvCreateMemStorage;
import static com.googlecode.javacv.cpp.opencv_core.cvDrawContours;
import static com.googlecode.javacv.cpp.opencv_core.cvGetSeqElem;
import static com.googlecode.javacv.cpp.opencv_core.cvGetSize;
import static com.googlecode.javacv.cpp.opencv_core.cvPoint;
import static com.googlecode.javacv.cpp.opencv_core.cvResetImageROI;
import static com.googlecode.javacv.cpp.opencv_core.cvScalarAll;
import static com.googlecode.javacv.cpp.opencv_core.cvSet;
import static com.googlecode.javacv.cpp.opencv_core.cvSetImageROI;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_CHAIN_APPROX_NONE;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_GAUSSIAN;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_MEDIAN;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_POLY_APPROX_DP;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_RETR_LIST;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_RETR_TREE;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_RGB2GRAY;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_RGBA2GRAY;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_THRESH_BINARY;
import static com.googlecode.javacv.cpp.opencv_imgproc.CV_THRESH_OTSU;
import static com.googlecode.javacv.cpp.opencv_imgproc.cv2DRotationMatrix;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvApproxPoly;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvBoundingRect;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvContourArea;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvContourPerimeter;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvCvtColor;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvDilate;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvErode;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvFindContours;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvMinAreaRect2;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvSmooth;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvThreshold;
import static com.googlecode.javacv.cpp.opencv_imgproc.cvWarpAffine;

import java.io.File;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.Paint;
import android.net.Uri;
import android.os.Environment;
import android.util.Log;

import com.googlecode.javacpp.Loader;
import com.googlecode.javacv.cpp.opencv_core.CvBox2D;
import com.googlecode.javacv.cpp.opencv_core.CvContour;
import com.googlecode.javacv.cpp.opencv_core.CvMat;
import com.googlecode.javacv.cpp.opencv_core.CvMemStorage;
import com.googlecode.javacv.cpp.opencv_core.CvPoint;
import com.googlecode.javacv.cpp.opencv_core.CvPoint2D32f;
import com.googlecode.javacv.cpp.opencv_core.CvRect;
import com.googlecode.javacv.cpp.opencv_core.CvSeq;
import com.googlecode.javacv.cpp.opencv_core.CvSize;
import com.googlecode.javacv.cpp.opencv_core.IplImage;

public class ImagingInterfaces {

	public static IplImage performEdgeDetection(Bitmap openCVBitmap)
	{	    
		IplImage tmp = cvCreateImage(new CvSize(openCVBitmap.getWidth(), openCVBitmap.getHeight()), 8, 4);
		openCVBitmap.copyPixelsToBuffer(tmp.getByteBuffer());
		IplImage openCVImg = cvCreateImage(cvGetSize(tmp), 8, 3);
		cvCvtColor(tmp, openCVImg, 1);
		tmp.release();
		
		IplImage grayImage = cvCreateImage(cvGetSize(openCVImg), 8, 1);
	    IplImage maskImage = cvCreateImage(cvGetSize(openCVImg), 8, 1);
	    IplImage outputImage = cvCreateImage(cvGetSize(openCVImg), 8, openCVImg.nChannels());
	    
	    cvSet(maskImage, CV_RGB(0, 0, 0));
	    cvSet(outputImage, CV_RGB(0, 0, 0));
	    
	    cvCvtColor(openCVImg, grayImage, CV_RGBA2GRAY);
        cvSmooth( grayImage, grayImage, CV_GAUSSIAN, 25); 
        
        CvMemStorage mem;
        CvSeq contours = new CvSeq();
        CvSeq ptr = new CvSeq();
        //cvThreshold(grayImage, grayImage, 75, 200, CV_THRESH_BINARY);
        //don't make the third value <50
        //cvThreshold(grayImage, grayImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
        double otsu = cvThreshold(grayImage, grayImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
        //cvDilate(grayImage, grayImage, null, 2);
        
        /*
        File out2 = new File("outT" + prefix + ".jpg");
	    if(out2.exists())
	    	out2.delete();
	    
		try {
			ImageIO.write(grayImage.getBufferedImage(), "jpg", out2);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		*/
        
        //cvAdaptiveThreshold(grayImage, grayImage, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 15, 5);
        int leftX = openCVImg.width(), rightX = 1, bottomY = openCVImg.height(), topY = 1;
        int area = grayImage.width() * grayImage.height();
        ArrayList<Double> potentialDegrees = new ArrayList<Double>();
        ArrayList<CvPoint> pts = new ArrayList<CvPoint>();
		
		int foundSigns = 0;
		for(int attempts = 0; attempts < 5; attempts++)
		{
			foundSigns = 0;
			mem = cvCreateMemStorage(0);
			
	        cvFindContours(grayImage, mem, contours, sizeof(CvContour.class) , CV_RETR_TREE, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
	        if(contours.total() == 0)
	        	System.out.println("none");
	        
	        for(ptr = contours; ptr != null ; ptr = ptr.h_next())
	        {      
	        	for(CvSeq ptr2 = ptr.v_next(); ptr2 != null; ptr2 = ptr2.h_next())
	        	{
	        		CvSeq result = cvApproxPoly( ptr2, Loader.sizeof(CvContour.class), mem,
	                        CV_POLY_APPROX_DP, cvContourPerimeter(ptr2)*.01, 0 );
	            	
	            	if(result.total() <= 8 && cvContourArea(ptr2, CV_WHOLE_SEQ, 0) > area/100)
	            	{
	            		foundSigns++;
	            		CvRect rect = cvBoundingRect(ptr2, 0);  
	            		CvBox2D minRect = cvMinAreaRect2(ptr2, null);
	            		
	            		potentialDegrees.add((double) minRect.angle());

	            		cvDrawContours(maskImage, ptr2, cvScalarAll(255), cvScalarAll(255), 0, CV_FILLED, 8, cvPoint(0,0));
	            		
	            		pts.add(new CvPoint(cvGetSeqElem(ptr, 0)));
	            		
	            		leftX = rect.x() < leftX ? rect.x() : leftX;
	            		rightX = rect.x() + rect.width() > rightX ? rect.x() + rect.width() : rightX;
	            		bottomY = rect.y() < bottomY ? rect.y() : bottomY;
	            		topY = rect.y() + rect.height() > topY ? rect.y() + rect.height() : topY;
	            	}
	            	
	            	for(CvSeq ptr3 = ptr2.v_next(); ptr3 != null; ptr3 = ptr3.h_next())
	            	{
	            		CvRect rect3 = cvBoundingRect(ptr3, 0); 
	            		if(rect3.width() > openCVImg.width()/2)
	            			cvDrawContours(maskImage, ptr3, cvScalarAll(0), cvScalarAll(0), 0, CV_FILLED, 8, cvPoint(0,0));
	            	}
	        	}
	        }
	        
	        if(foundSigns > 0)
	        	break;
	        
	        cvCvtColor(openCVImg, grayImage, CV_RGBA2GRAY);
	        cvSmooth( grayImage, grayImage, CV_GAUSSIAN, 25); 
	        otsu -= 5;
	        cvThreshold(grayImage, grayImage, otsu, 255, CV_THRESH_BINARY);
		}
		
		if(foundSigns == 0)
		{
			outputImage = cvCreateImage(cvGetSize(grayImage), 8, 4);
		    cvSet(outputImage, CV_RGB(0, 0, 0));
		    return outputImage;
		}
        
	    
        cvErode(maskImage, maskImage, null, 10);
        cvSmooth(maskImage, maskImage, CV_MEDIAN, 15);
        cvCopy(openCVImg, outputImage, maskImage);
        cvCopy(outputImage, openCVImg);
        
        grayImage = cvCreateImage(cvGetSize(openCVImg), 8, 1);
        cvCvtColor(openCVImg, grayImage, CV_RGBA2GRAY);
        otsu = cvThreshold(grayImage, grayImage, 125, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
        
        if(otsu < 100)
        {
        	grayImage = cvCreateImage(cvGetSize(openCVImg), 8, 1);
            cvCvtColor(openCVImg, grayImage, CV_RGBA2GRAY);
            otsu = cvThreshold(grayImage, grayImage, 100, 255, CV_THRESH_BINARY);
        }

        if(leftX < rightX && bottomY < topY)
        {
	        CvRect roiRect = new CvRect(leftX, bottomY, rightX - leftX, topY - bottomY);
		    cvSetImageROI(grayImage, roiRect);
		    tmp = cvCreateImage(cvGetSize(grayImage), grayImage.depth(), grayImage.nChannels());
		    cvCopy(grayImage, tmp, null);
		    cvResetImageROI(grayImage);
		    grayImage.release();
		    grayImage = tmp;
        }
        
        if(potentialDegrees.size() > 0)
        {  
        	double avgAngle = 0;
        	for(double angle : potentialDegrees)
        		avgAngle += angle;
        	avgAngle /= potentialDegrees.size();

	        double radians = Math.toRadians(avgAngle);
	        System.out.println(":degrees to rotate: " + avgAngle);
	
	        if(Math.abs(avgAngle) < 30)
	        {
	        	double sin = Math.abs(Math.sin(radians));
	    		double cos = Math.abs(Math.cos(radians));
	    		
	    		int newWidth = (int) (grayImage.width() * cos + grayImage.height() * sin);
	    		int newHeight = (int) (grayImage.width() * sin + grayImage.height() * cos);
	    	    
	    	    CvPoint2D32f center = new CvPoint2D32f(newWidth/2, newHeight/2);
	    	    CvSize targetSize = new CvSize(newWidth, newHeight);
	    	    	    
	    	    int offsetX = (newWidth - grayImage.width()) / 2;
	    	    int offsetY = (newHeight - grayImage.height()) / 2;
	    	    
	    	    IplImage enlargedImage = cvCreateImage(targetSize, grayImage.depth(), grayImage.nChannels());
	    	    CvRect roiRect = new CvRect(offsetX, offsetY, grayImage.width(), grayImage.height());
	    	    cvSetImageROI(enlargedImage, roiRect);
	    	    cvCopy(grayImage, enlargedImage);
	    	    cvResetImageROI(enlargedImage);
	    	    
	    	    CvMat rotMat = cvCreateMat(2, 3, CV_32F);
	    	    rotMat = cv2DRotationMatrix(center, avgAngle, 1.0, rotMat);
	    	    cvWarpAffine(enlargedImage, enlargedImage, rotMat);
	    	    grayImage.release();
	    	    grayImage = enlargedImage;
	        }
        }
        
        cvSmooth(grayImage, grayImage, CV_MEDIAN, 3);
        
        tmp = cvCreateImage(cvGetSize(grayImage), 8, 1);
        mem = cvCreateMemStorage(0);
        
        cvCopy(grayImage, tmp);
        cvFindContours(grayImage, mem, contours, sizeof(CvContour.class) , CV_RETR_LIST, CV_CHAIN_APPROX_NONE, cvPoint(0,0));
        cvCopy(tmp, grayImage);
        
        for(ptr = contours; ptr != null ; ptr = ptr.h_next())
        {
        	CvRect rect = cvBoundingRect(ptr, 0);
        	if(rect.width() > (grayImage.width()/2) || rect.height() > (grayImage.height()/(1.5)))
        		cvDrawContours(grayImage, ptr, cvScalarAll(0), cvScalarAll(0), 0, CV_FILLED, 8, cvPoint(0,0));
        }
        
       cvErode(grayImage, grayImage, null, 2);
       cvDilate(grayImage, grayImage, null, 1);

	    outputImage = cvCreateImage(cvGetSize(grayImage), 8, 4);
	    cvCvtColor(grayImage,outputImage, 9);
	    return outputImage;
	}

	static Bitmap toGrayscale(Bitmap bmpOriginal)
	{        
	    int width, height;
	    height = bmpOriginal.getHeight();
	    width = bmpOriginal.getWidth();    
	
	    Bitmap bmpGrayscale = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
	    Canvas c = new Canvas(bmpGrayscale);
	    Paint paint = new Paint();
	    ColorMatrix cm = new ColorMatrix();
	    cm.setSaturation(0);
	    ColorMatrixColorFilter f = new ColorMatrixColorFilter(cm);
	    paint.setColorFilter(f);
	    c.drawBitmap(bmpOriginal, 0, 0, paint);
	    return bmpGrayscale;
	}

	public static File getOutputMediaFile(int type){
	    // To be safe, you should check that the SDCard is mounted
	    // using Environment.getExternalStorageState() before doing this.
	
	    File mediaStorageDir = new File(Environment.getExternalStoragePublicDirectory(
	              Environment.DIRECTORY_PICTURES), "MyCameraApp");
	    // This location works best if you want the created images to be shared
	    // between applications and persist after your app has been uninstalled.
	
	    // Create the storage directory if it does not exist
	    if (! mediaStorageDir.exists()){
	        if (! mediaStorageDir.mkdirs()){
	            Log.d("MyCameraApp", "failed to create directory");
	            return null;
	        }
	    }
	
	    // Create a media file name
	    String timeStamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
	    File mediaFile;
	    if (type == ManualModeFragment.MEDIA_TYPE_IMAGE){
	        mediaFile = new File(mediaStorageDir.getPath() + File.separator +
	        "IMG_"+ timeStamp + ".jpg");
	    } else if(type == ManualModeFragment.MEDIA_TYPE_VIDEO) {
	        mediaFile = new File(mediaStorageDir.getPath() + File.separator +
	        "VID_"+ timeStamp + ".mp4");
	    } else {
	        return null;
	    }
	
	    return mediaFile;
	}

	/** Create a file Uri for saving an image or video */
	public static Uri getOutputMediaFileUri(int type){
	      return Uri.fromFile(getOutputMediaFile(type));
	}
	
	public static Bitmap changeBitmapContrastBrightness(Bitmap bmp, float contrast, float brightness)
	{
	    ColorMatrix cm = new ColorMatrix(new float[]
	            {
	                contrast, 0, 0, 0, brightness,
	                0, contrast, 0, 0, brightness,
	                0, 0, contrast, 0, brightness,
	                0, 0, 0, 1, 0
	            });

	    Bitmap ret = Bitmap.createBitmap(bmp.getWidth(), bmp.getHeight(), bmp.getConfig());

	    Canvas canvas = new Canvas(ret);

	    Paint paint = new Paint();
	    paint.setColorFilter(new ColorMatrixColorFilter(cm));
	    canvas.drawBitmap(bmp, 0, 0, paint);

	    return ret;
	}

}
