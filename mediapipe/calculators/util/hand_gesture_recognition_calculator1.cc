#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "mediapipe/framework/formats/rect.pb.h"
#include "absl/strings/str_cat.h"
#include "mediapipe/framework/formats/video_stream_header.h"
#include "mediapipe/framework/port/ret_check.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/port/statusor.h"
#include "mediapipe/util/color.pb.h"
#include "mediapipe/util/render_data.pb.h"
#include "mediapipe/gpu/gpu_buffer.h"

namespace mediapipe
{
constexpr char normalizedLandmarkListTag[] = "NORM_LANDMARKS";
constexpr char kLandmarksTag[] = "LANDMARKS";
constexpr char kNormLandmarksTag[] = "NORM_LANDMARKS";
constexpr char recognizedHandGestureTag[] = "RECOGNIZED_HAND_GESTURE1";
constexpr char kRenderDataTag[] = "RENDER_DATA";
constexpr char kGpuBufferTag[] = "IMAGE_GPU";

// Graph config:
// node {
//   calculator: "HandGestureRecognitionCalculator1"
//   input_stream: "NORM_LANDMARKS:scaled_landmarks"
//   input_stream: "NORM_RECT:hand_rect_for_next_frame"
// }

class HandGestureRecognitionCalculator1 : public CalculatorBase
{
public:
    static absl::Status GetContract(CalculatorContract *cc);
    absl::Status Open(CalculatorContext *cc) override;
    absl::Status Process(CalculatorContext *cc) override;

private:
 /*   float get_Euclidean_DistanceAB(float a_x, float a_y, float b_x, float b_y)
    {
        float dist = std::pow(a_x - b_x, 2) + pow(a_y - b_y, 2);
        return std::sqrt(dist);
    }

    bool isThumbNearFirstFinger(NormalizedLandmark point1, NormalizedLandmark point2)
    {
        float distance = this->get_Euclidean_DistanceAB(point1.x(), point1.y(), point2.x(), point2.y());
        return distance < 0.1;
    }*/
};

REGISTER_CALCULATOR(HandGestureRecognitionCalculator1);

absl::Status HandGestureRecognitionCalculator1::GetContract(CalculatorContract *cc)
{
    LOG(INFO) << "hand GetContract";

    RET_CHECK(cc->Inputs().HasTag(kGpuBufferTag));
    cc->Inputs().Tag(kGpuBufferTag).Set<mediapipe::GpuBuffer>();

    //RET_CHECK(cc->Inputs().HasTag(normalizedLandmarkListTag));
    //cc->Inputs().Tag(normalizedLandmarkListTag).Set<NormalizedLandmarkList>();
    
    /*RET_CHECK(cc->Inputs().HasTag(kNormLandmarksTag));
    if (cc->Inputs().HasTag(kNormLandmarksTag)) {
        cc->Inputs().Tag(kNormLandmarksTag).Set<NormalizedLandmarkList>();
    }*/

    RET_CHECK(cc->Outputs().HasTag(kRenderDataTag));
    cc->Outputs().Tag(kRenderDataTag).Set<RenderData>();

    return absl::OkStatus();
}

absl::Status HandGestureRecognitionCalculator1::Open(CalculatorContext *cc)
{
    cc->SetOffset(TimestampDiff(0));
    LOG(INFO) << "hand Open";
    return absl::OkStatus();
}

absl::Status HandGestureRecognitionCalculator1::Process(CalculatorContext *cc)
{

    LOG(INFO) << "hand Process";
    if (cc->Inputs().HasTag(kGpuBufferTag) && cc->Inputs().Tag(kGpuBufferTag).IsEmpty()) {
        LOG(INFO) << "hand Process empty1";
        return absl::OkStatus();
    }
 
    if (cc->Inputs().HasTag(kNormLandmarksTag) && cc->Inputs().Tag(kNormLandmarksTag).IsEmpty()) {
        LOG(INFO) << "hand Process empty2";
        return absl::OkStatus();
    }
    //if (cc->Inputs().HasTag(normalizedLandmarkListTag) && cc->Inputs().Tag(normalizedLandmarkListTag).IsEmpty()) {
    //    LOG(INFO) << "hand Process empty2";
    //    return absl::OkStatus();
    // }
    
/*  //std::string *recognized_hand_gesture;
    auto recognized_hand_gesture = absl::make_unique<std::string>();
    if (cc->Inputs().HasTag(normalizedLandmarkListTag) && cc->Inputs().Tag(normalizedLandmarkListTag).IsEmpty()) {
        LOG(INFO) << "No Hand Detected";
        return absl::OkStatus();
    }

    // hand closed (red) rectangle
        
    if (cc->Inputs().HasTag(normalizedLandmarkListTag)) {
        const auto &landmarkList=
        cc->Inputs().Tag(normalizedLandmarkListTag).Get<NormalizedLandmarkList>();
    
        // finger states
        bool thumbIsOpen = false;
        bool firstFingerIsOpen = false;
        bool secondFingerIsOpen = false;
        bool thirdFingerIsOpen = false;
        bool fourthFingerIsOpen = false;
        //

        float pseudoFixKeyPoint = landmarkList.landmark(2).x();
        if (landmarkList.landmark(3).x() < pseudoFixKeyPoint && landmarkList.landmark(4).x() < pseudoFixKeyPoint)
        {
            thumbIsOpen = true;
        }

        pseudoFixKeyPoint = landmarkList.landmark(6).y();
        if (landmarkList.landmark(7).y() < pseudoFixKeyPoint && landmarkList.landmark(8).y() < pseudoFixKeyPoint)
        {
            firstFingerIsOpen = true;
        }

        pseudoFixKeyPoint = landmarkList.landmark(10).y();
        if (landmarkList.landmark(11).y() < pseudoFixKeyPoint && landmarkList.landmark(12).y() < pseudoFixKeyPoint)
        {
            secondFingerIsOpen = true;
        }

        pseudoFixKeyPoint = landmarkList.landmark(14).y();
        if (landmarkList.landmark(15).y() < pseudoFixKeyPoint && landmarkList.landmark(16).y() < pseudoFixKeyPoint)
        {
            thirdFingerIsOpen = true;
        }

        pseudoFixKeyPoint = landmarkList.landmark(18).y();
        if (landmarkList.landmark(19).y() < pseudoFixKeyPoint && landmarkList.landmark(20).y() < pseudoFixKeyPoint)
        {
            fourthFingerIsOpen = true;
        }

        // Hand gesture recognition
        if (thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && thirdFingerIsOpen && fourthFingerIsOpen)
        {
            //recognized_hand_gesture = new std::string("FIVE");
            *recognized_hand_gesture = "FIVE";
        }
        else if (!thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && thirdFingerIsOpen && fourthFingerIsOpen)
        {
            //recognized_hand_gesture = new std::string("FOUR");
            *recognized_hand_gesture = "FIVE";
        }
        else if (thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen)
        {
            //recognized_hand_gesture = new std::string("TREE");
            *recognized_hand_gesture = "FIVE";
        }
        else if (thumbIsOpen && firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen)
        {
            //recognized_hand_gesture = new std::string("TWO");
        }
        else if (!thumbIsOpen && firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen)
        {
            //recognized_hand_gesture = new std::string("ONE");
        }
        else if (!thumbIsOpen && firstFingerIsOpen && secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen)
        {
            //recognized_hand_gesture = new std::string("YEAH");
        }
        else if (!thumbIsOpen && firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && fourthFingerIsOpen)
        {
            //recognized_hand_gesture = new std::string("ROCK");
        }
        else if (thumbIsOpen && firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && fourthFingerIsOpen)
        {
            //recognized_hand_gesture = new std::string("SPIDERMAN");
        }
        else if (!thumbIsOpen && !firstFingerIsOpen && !secondFingerIsOpen && !thirdFingerIsOpen && !fourthFingerIsOpen)
        {
            //recognized_hand_gesture = new std::string("FIST");
        }
        else if (!firstFingerIsOpen && secondFingerIsOpen && thirdFingerIsOpen && fourthFingerIsOpen && this->isThumbNearFirstFinger(landmarkList.landmark(4), landmarkList.landmark(8)))
        {
            //recognized_hand_gesture = new std::string("OK");
        }
        else
        {
            //recognized_hand_gesture = new std::string("___");
            LOG(INFO) << "Finger States: " << thumbIsOpen << firstFingerIsOpen << secondFingerIsOpen << thirdFingerIsOpen << fourthFingerIsOpen;       
        }
        LOG(INFO) <<landmarkList.landmark_size()<<','<< *recognized_hand_gesture;
    }
    //cc->Outputs().Tag(recognizedHandGestureTag).Add(recognized_hand_gesture, cc->InputTimestamp());
    //cc->Outputs().Tag(recognizedHandGestureTag).Add(recognized_hand_gesture.release(), cc->InputTimestamp());
*/
    std::string given_string = "test";
    //LOG(INFO) << given_string;
    auto render_data = absl::make_unique<RenderData>();

    //if (cc->Inputs().HasTag(kGpuBufferTag)) {   
    if (cc->Inputs().HasTag(kNormLandmarksTag)) {    
        auto* label_annotation = render_data->add_render_annotations();
        auto* text = label_annotation->mutable_text();
        text->set_display_text(given_string);
        text->set_font_height(100);
        text->set_normalized(false);
        text->set_left(100);
        text->set_baseline(100);
        label_annotation->mutable_color()->set_r(255);
        label_annotation->mutable_color()->set_g(0);
        label_annotation->mutable_color()->set_b(0);
        label_annotation->set_thickness(3); 
    }   

    cc->Outputs().Tag(kRenderDataTag).Add(render_data.release(), cc->InputTimestamp());
    LOG(INFO) << "hand Process end";
    return absl::OkStatus();  
} 

} // namespace mediapipe
