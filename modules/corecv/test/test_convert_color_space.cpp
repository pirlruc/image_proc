#include <gtest/gtest.h>

#include <improc/services/convert_color_space.hpp>

TEST(ConvertColorSpace,TestLoadWithoutToColorSpace) {
    servproc::JsonFile json_file {"../../test/data/test_color_conversion_without_to.json"};
    Json::Value json_content = json_file.Read();

    improc::StringKeyConvertColorSpace convert {};
    EXPECT_THROW(convert.Load(json_content),improc::file_processing_error);
}

TEST(ConvertColorSpace,TestLoadWithFromColorSpaceArray) {
    servproc::JsonFile json_file {"../../test/data/test_color_conversion_with_from_array.json"};
    Json::Value json_content = json_file.Read();

    improc::StringKeyConvertColorSpace convert {};
    EXPECT_THROW(convert.Load(json_content),Json::LogicError);
}

TEST(ConvertColorSpace,TestWithoutFromColorSpace) {
    servproc::JsonFile json_file {"../../test/data/test_color_conversion_without_from.json"};
    Json::Value json_content = json_file.Read();

    improc::StringKeyConvertColorSpace convert {};
    convert.Load(json_content);

    cv::Mat             image_data       = cv::Mat::ones(10,5,CV_8UC3);
    improc::ColorSpace  from_color_space = improc::ColorSpace::kRGB;
    servproc::StringKeyContext cntxt {};
    cntxt.Add("image",image_data);
    cntxt.Add("from_color_space",from_color_space);

    convert.Run(cntxt);    

    improc::ColorSpaceImage image = std::any_cast<improc::ColorSpaceImage>(cntxt["image"]);
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kGray);
    EXPECT_EQ(image.get_data().channels(),1);    
}

TEST(ConvertColorSpace,TestWithoutFromColorSpaceInContext) {
    servproc::JsonFile json_file {"../../test/data/test_color_conversion_without_from.json"};
    Json::Value json_content = json_file.Read();

    improc::StringKeyConvertColorSpace convert {};
    convert.Load(json_content);

    cv::Mat             image_data       = cv::Mat::ones(10,5,CV_8UC3);
    servproc::StringKeyContext cntxt {};
    cntxt.Add("image",image_data);

    EXPECT_THROW(convert.Run(cntxt),servproc::not_found_key);
}

TEST(ConvertColorSpace,TestWithFromColorSpaceSingleConversion) {
    servproc::JsonFile json_file {"../../test/data/test_single_color_conversion_with_from.json"};
    Json::Value json_content = json_file.Read();

    improc::StringKeyConvertColorSpace convert {};
    convert.Load(json_content);

    cv::Mat             image_data       = cv::Mat::ones(10,5,CV_8UC3);
    servproc::StringKeyContext cntxt {};
    cntxt.Add("image",image_data);

    convert.Run(cntxt);    

    improc::ColorSpaceImage image = std::any_cast<improc::ColorSpaceImage>(cntxt.Get("image"));
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kBGR);
    EXPECT_EQ(image.get_data().channels(),3);    
}

TEST(ConvertColorSpace,TestWithFromColorSpaceSequenceConversion) {
    servproc::JsonFile json_file {"../../test/data/test_sequence_color_conversion_with_from.json"};
    Json::Value json_content = json_file.Read();

    improc::StringKeyConvertColorSpace convert {};
    convert.Load(json_content);

    cv::Mat             image_data       = cv::Mat::ones(10,5,CV_8UC3);
    servproc::StringKeyContext cntxt {};
    cntxt.Add("image",image_data);

    convert.Run(cntxt);    

    improc::ColorSpaceImage image = std::any_cast<improc::ColorSpaceImage>(cntxt.Get("image"));
    EXPECT_EQ(image.get_color_space(),improc::ColorSpace::kGray);
    EXPECT_EQ(image.get_data().channels(),1);    
}
