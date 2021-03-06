/**
 * @file getValidDisparityROI.cpp
 * @brief mex interface for cv::getValidDisparityROI
 * @ingroup calib3d
 * @author Amro
 * @date 2015
 */
#include "mexopencv.hpp"
#include "opencv2/calib3d.hpp"
using namespace std;
using namespace cv;

/**
 * Main entry called from Matlab
 * @param nlhs number of left-hand-side arguments
 * @param plhs pointers to mxArrays in the left-hand-side
 * @param nrhs number of right-hand-side arguments
 * @param prhs pointers to mxArrays in the right-hand-side
 */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Check the number of arguments
    nargchk(nrhs>=2 && (nrhs%2)==0 && nlhs<=1);

    // Argument vector
    vector<MxArray> rhs(prhs, prhs+nrhs);

    // Option processing
    int minDisparity = 0;
    int numberOfDisparities = 64;
    int SADWindowSize = 21;
    for (int i=2; i<nrhs; i+=2) {
        string key(rhs[i].toString());
        if (key == "MinDisparity")
            minDisparity = rhs[i+1].toInt();
        else if (key == "NumDisparities")
            numberOfDisparities = rhs[i+1].toInt();
        else if (key == "BlockSize")
            SADWindowSize = rhs[i+1].toInt();
        else
            mexErrMsgIdAndTxt("mexopencv:error",
                "Unrecognized option %s", key.c_str());
    }

    // Process
    Rect roi1(rhs[0].toRect()),
         roi2(rhs[1].toRect()),
         r;
    r = getValidDisparityROI(roi1, roi2,
        minDisparity, numberOfDisparities, SADWindowSize);
    plhs[0] = MxArray(r);
}
