int main( int argc, char** argv )
{
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    Mat img0 = imread(filename, -1);
    if(img0.empty())
    {
     cout << "Couldn't open the image " << filename << ". Usage: inpaint 	<image_name>\n" << endl;
             return 0;
    }
    img = img0.clone();
    inpaintMask = Mat::zeros(img.size(), CV_8U);
    for(;;)
    {
        char c = (char)waitKey();
        if( c == 27 )
        break;
        if( c == 'r' )
        {
            inpaintMask = Scalar::all(0);
            img0.copyTo(img);
        }
    } return 0; }