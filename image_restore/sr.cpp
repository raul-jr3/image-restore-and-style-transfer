ImagingUnsharpMask(Imaging imOut, Imaging imIn, float radius, int percent,
                   		  int threshold)
{
    ImagingSectionCookie cookie;
    Imaging result; int x, y, diff;
    pixel *lineIn = NULL;
    pixel *lineOut = NULL;
    UINT8 *lineIn8 = NULL;
    UINT8 *lineOut8 = NULL;

    result = ImagingGaussianBlur(imOut, imIn, radius, 3);
    ImagingSectionEnter(&cookie);
    for (y = 0; y < imIn->ysize; y++) {
        if (imIn->image8)
       {
            for (x = 0; x < imIn->xsize; x++) {
                /* compare in/out pixels, apply sharpening */
                diff = lineIn8[x] - lineOut8[x];
                if (abs(diff) > threshold) {
                    /* add the diff*percent to the original pixel */
                    lineOut8[x] = clip8(lineIn8[x] + diff * percent / 100);
        } else {
                    /* new pixel is the same as imIn */
                    lineOut8[x] = lineIn8[x];
                   }
            }
        } else {
            lineIn = (pixel *)imIn->image32[y];
            lineOut = (pixel *)imOut->image32[y];
            for (x = 0; x < imIn->xsize; x++) {
                /* compare in/out pixels, apply sharpening */
                diff = lineIn[x][0] - lineOut[x][0];
                lineOut[x][0] = abs(diff) > threshold ?
                clip8(lineIn[x][0] + diff * percent / 100) : lineIn[x][0];
	    diff = lineIn[x][1] - lineOut[x][1];
                lineOut[x][1] = abs(diff) > threshold ?
                clip8(lineIn[x][1] + diff * percent / 100) : lineIn[x][1];
	    diff = lineIn[x][2] - lineOut[x][2];
                lineOut[x][2] = abs(diff) > threshold ?
                clip8(lineIn[x][2] + diff * percent / 100) : lineIn[x][2];
	    diff = lineIn[x][3] - lineOut[x][3];
                lineOut[x][3] = abs(diff) > threshold ?
                clip8(lineIn[x][3] + diff * percent / 100) : lineIn[x][3];
}}}