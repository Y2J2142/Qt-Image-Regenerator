#include "img_generator.hpp"

void generate(Mat src, Mat dst, int limit, int size, int range_begin, int range_end, RNG& rng)
 {
    Mat img1(src.size().height, src.size().width, CV_8UC3, Scalar(255,255,255));
    Mat img2(src.size().height, src.size().width, CV_8UC3, Scalar(255,255,255));


    for(auto i = 0; i<limit;i++)
    {
        Point point(rng.uniform(range_begin, range_end), rng.uniform(0, src.size().height));
        Vec3b colour = src.at<Vec3b>(point);
        Scalar colour_scalar(colour[0], colour[1], colour[2]);

        Point pnt1((point.x - size) > 0 ? point.x - size : 0, (point.y - size) > 0 ? point.y - size : 0);
        Point pnt2(min(src.cols, point.x + size), min(src.rows, point.y + size));


        Mat src_cmpr_part(src, Rect(pnt1, pnt2));
        Mat img1_cmpr_part(img1, Rect(pnt1, pnt2));
        Mat img2_cmpr_part(img2, Rect(pnt1, pnt2));


        auto src_to_img1 = norm(src_cmpr_part, img1_cmpr_part, NORM_INF);
        auto src_to_img2 = norm(src_cmpr_part, img2_cmpr_part, NORM_INF);
        if(src_to_img1 < src_to_img2)
        {
            Mat temp1(img1, Rect(pnt1, pnt2));
            Mat temp2(img2, Rect(pnt1, pnt2));
            memcpy(temp1.data, temp2.data, sizeof(temp2.data));
        }
        else
        {
                circle(img2, point, size, colour_scalar, -1);
                circle(dst, point, size, colour_scalar, -1);
        }

    }

     return;
}
