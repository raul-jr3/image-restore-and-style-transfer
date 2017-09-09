static void fastNlMeansDenoising( const Mat& src, Mat& dst, const std::vector<float>& h, int templateWindowSize, int searchWindowSize)
{
    int hn = (int)h.size();
    double granularity = (double)std::max(1., (double)dst.total()/(1 << 17));
    switch (CV_MAT_CN(src.type())) {
        case 1:
            parallel_for_(cv::Range(0, src.rows),
                          FastNlMeansDenoisingInvoker<ST, IT, UIT, D, int>(
                          src, dst, templateWindowSize, searchWindowSize, &h[0]),
                          granularity);
            break;
        case 2:
            if (hn == 1){
                parallel_for_(cv::Range(0, src.rows),
                              FastNlMeansDenoisingInvoker<Vec<ST, 2>, IT, UIT, D, int>(
                              src, dst, templateWindowSize, searchWindowSize, &h[0]),
                              granularity);}
            else{
                parallel_for_(cv::Range(0, src.rows),
                              FastNlMeansDenoisingInvoker<Vec<ST, 2>, IT, UIT, D, Vec2i>(
                              src, dst, templateWindowSize, searchWindowSize, &h[0]),
                              granularity);}
            break;
        case 3:
            if (hn == 1){
                parallel_for_(cv::Range(0, src.rows),
                              FastNlMeansDenoisingInvoker<Vec<ST, 3>, IT, UIT, D, int>(
                              src, dst, templateWindowSize, searchWindowSize, &h[0]),
                              granularity);}
            else{
                parallel_for_(cv::Range(0, src.rows),
                              FastNlMeansDenoisingInvoker<Vec<ST, 3>, IT, UIT, D, Vec3i>(
                              src, dst, templateWindowSize, searchWindowSize, &h[0]),
                              granularity); }
            break;
        case 4:
            if (hn == 1){
                parallel_for_(cv::Range(0, src.rows),
                              FastNlMeansDenoisingInvoker<Vec<ST, 4>, IT, UIT, D, int>(
                              src, dst, templateWindowSize, searchWindowSize, &h[0]),
                              granularity);}
            else{
                parallel_for_(cv::Range(0, src.rows),
                              FastNlMeansDenoisingInvoker<Vec<ST, 4>, IT, UIT, D, Vec4i>(
                              src, dst, templateWindowSize, searchWindowSize, &h[0]),
                              granularity);}
            break;
        default:
            CV_Error(Error::StsBadArg,
                     "Unsupported number of channels! Only 1, 2, 3, and 4 are supported");
    }}