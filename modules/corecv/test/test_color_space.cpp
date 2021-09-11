#include <gtest/gtest.h>

#include <improc/corecv/color_space.hpp>

TEST(ColorSpace,TestEmptyColorSpaceConstructor) {
    improc::ColorSpace color_space {};
    EXPECT_EQ(color_space,improc::ColorSpace::Value::kRGB);
}

TEST(ColorSpace,TestConstructorFromValue) {
    improc::ColorSpace color_space {improc::ColorSpace::Value::kRGBA};
    EXPECT_EQ(color_space,improc::ColorSpace::Value::kRGBA);
}

TEST(ColorSpace,TestConstructorFromLowerString) {
    improc::ColorSpace color_space_bgr {"bgr"};
    improc::ColorSpace color_space_rgb {"rgb"};
    improc::ColorSpace color_space_bgra{"bgra"};
    improc::ColorSpace color_space_rgba{"rgba"};
    improc::ColorSpace color_space_gray{"gray"};
    EXPECT_EQ(color_space_bgr ,improc::ColorSpace::Value::kBGR );
    EXPECT_EQ(color_space_rgb ,improc::ColorSpace::Value::kRGB );
    EXPECT_EQ(color_space_bgra,improc::ColorSpace::Value::kBGRA);
    EXPECT_EQ(color_space_rgba,improc::ColorSpace::Value::kRGBA);
    EXPECT_EQ(color_space_gray,improc::ColorSpace::Value::kGray);
}

TEST(ColorSpace,TestConstructorFromUpperString) {
    improc::ColorSpace color_space_bgr {"BGR"};
    improc::ColorSpace color_space_rgb {"RGB"};
    improc::ColorSpace color_space_bgra{"BGRA"};
    improc::ColorSpace color_space_rgba{"RGBA"};
    improc::ColorSpace color_space_gray{"GRAY"};
    EXPECT_EQ(color_space_bgr ,improc::ColorSpace::Value::kBGR );
    EXPECT_EQ(color_space_rgb ,improc::ColorSpace::Value::kRGB );
    EXPECT_EQ(color_space_bgra,improc::ColorSpace::Value::kBGRA);
    EXPECT_EQ(color_space_rgba,improc::ColorSpace::Value::kRGBA);
    EXPECT_EQ(color_space_gray,improc::ColorSpace::Value::kGray);
}

TEST(ColorSpace,TestInvalidStringConstructor) {
    EXPECT_THROW(improc::ColorSpace color_space {"invalid"},std::out_of_range);
}

TEST(ColorSpace,TestConstructorFromClass) {
    EXPECT_EQ(improc::ColorSpace::kBGR ,improc::ColorSpace::Value::kBGR);
    EXPECT_EQ(improc::ColorSpace::kRGB ,improc::ColorSpace::Value::kRGB);
    EXPECT_EQ(improc::ColorSpace::kBGRA,improc::ColorSpace::Value::kBGRA);
    EXPECT_EQ(improc::ColorSpace::kRGBA,improc::ColorSpace::Value::kRGBA);
    EXPECT_EQ(improc::ColorSpace::kGray,improc::ColorSpace::Value::kGray);
}

TEST(ColorSpace,TestToString) {
    improc::ColorSpace color_space_rgba {improc::ColorSpace::Value::kRGBA};
    EXPECT_EQ(color_space_rgba.ToString(),"RGBA");
}
