#include "absl/memory/memory.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/calculator_options.pb.h"
#include "mediapipe/framework/formats/detection.pb.h"
#include "mediapipe/framework/formats/location_data.pb.h"
#include "mediapipe/framework/port/ret_check.h"
#include "mediapipe/util/color.pb.h"
#include "mediapipe/util/render_data.pb.h"

#include <math.h>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "absl/strings/str_cat.h"
//#include "mediapipe/calculators/util/labels_to_render_data_calculator.pb.h"
#include "mediapipe/framework/calculator_framework.h"
//#include "mediapipe/framework/formats/classification.pb.h"
#include "mediapipe/framework/formats/video_stream_header.h"
#include "mediapipe/framework/port/ret_check.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/port/statusor.h"
#include "mediapipe/util/color.pb.h"
#include "mediapipe/util/render_data.pb.h"

namespace mediapipe{

    //constexpr char STRING[] = "STRING";
    constexpr char STRING[] = "RECOGNIZED_HAND_GESTURE1";
    constexpr char kRenderDataTag[] = "RENDER_DATA";

    class StringToRenderDataCalculator : public CalculatorBase {
        public:
        //StringToRenderDataCalculator(){};
        //~StringToRenderDataCalculator(){};

        static absl::Status GetContract(CalculatorContract* cc);
        absl::Status Open(CalculatorContext* cc)override;
        absl::Status Process(CalculatorContext* cc)override;
        private:
        

    };
    REGISTER_CALCULATOR(StringToRenderDataCalculator);


    absl::Status StringToRenderDataCalculator::GetContract(CalculatorContract* cc){
        LOG(INFO) <<"string to render1";
        cc->Inputs().Tag(STRING).Set<std::string>();
        cc->Outputs().Tag(kRenderDataTag).Set<RenderData>();
        return absl::OkStatus();
    }
    absl::Status StringToRenderDataCalculator::Open(CalculatorContext* cc){
        return absl::OkStatus();
    }
    absl::Status StringToRenderDataCalculator::Process(CalculatorContext* cc){
        LOG(INFO) <<"string to render2";

        std::string given_string = cc->Inputs().Tag(STRING).Get<std::string>();
        //std::string given_string = "test";
        LOG(INFO) << given_string;

        //std::string given_string = "test";
        //auto render_data = absl::make_unique<RenderData>();
        RenderData render_data;
        auto* label_annotation = render_data.add_render_annotations();
        auto* text = label_annotation->mutable_text();
        text->set_display_text(given_string);
        text->set_font_height(80);
        text->set_normalized(false);
        text->set_left(350);
        text->set_baseline(450);
        label_annotation->mutable_color()->set_r(0);
        label_annotation->mutable_color()->set_g(0);
        label_annotation->mutable_color()->set_b(0);
        label_annotation->set_thickness(3);

        auto* label_annotation_other = render_data.add_render_annotations();
        auto* text_other = label_annotation_other->mutable_text();
        text_other->set_display_text(given_string);
        text_other->set_font_height(80);
        text_other->set_normalized(false);
        text_other->set_left(349);
        text_other->set_baseline(451);
        label_annotation->mutable_color()->set_r(256);
        label_annotation->mutable_color()->set_g(256);
        label_annotation->mutable_color()->set_b(256);
        label_annotation->set_thickness(3);

        //cc->Outputs().Tag(kRenderDataTag).Add(render_data.release(), cc->InputTimestamp());
        
        cc->Outputs().Tag(kRenderDataTag).AddPacket(MakePacket<RenderData>(render_data).At(cc->InputTimestamp()));
        return absl::OkStatus();
    }
    /*::mediapipe::Status Close(CalculatorContext* cc){
        return ::mediapipe::OkStatus();
    }*/

}