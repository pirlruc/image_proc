#include <gtest/gtest.h>

#include <improc/corecv/image.h>

TEST(Image,TestEmptyImageConstructor) {
    improc::Image image_empty {};
    EXPECT_TRUE(image_empty.get_data().empty());
}

TEST(Image,TestSetImageToEmptyImage) {
    improc::Image image {};
    image.set_data(cv::Mat::zeros(10,10,CV_8U));
    EXPECT_FALSE(image.get_data().empty());
}

TEST(Image,TestSetInvalidImage) {
    improc::Image image {};
    EXPECT_THROW(image.set_data(cv::Mat::zeros(10,10,CV_16S)),improc::not_supported_data_type);
}

TEST(Image,TestImageConstructor) {
    improc::Image image {cv::Mat::zeros(10,10,CV_8U)};
    EXPECT_FALSE(image.get_data().empty());
}

TEST(Image,TestInvalidImageConstructor) {
    EXPECT_THROW(improc::Image image {cv::Mat::zeros(10,10,CV_16S)},improc::not_supported_data_type);
}

TEST(Image,TestGetImage) {
    cv::Mat image_data = cv::Mat::ones(3,5,CV_8U);
    improc::Image image {image_data};
    EXPECT_EQ(image.get_data().at<uint8_t>(0,0),1);
    image_data.at<uint8_t>(0,0) = 20;
    EXPECT_EQ(image.get_data().at<uint8_t>(0,0),20);
}

TEST(Image,TestCloneImage) {
    cv::Mat image_data = cv::Mat::ones(3,5,CV_8U);
    improc::Image image {image_data};
    improc::Image clone = image.clone();
    EXPECT_EQ(clone.get_data().at<uint8_t>(0,0),1);
    image_data.at<uint8_t>(0,0) = 20;
    EXPECT_EQ(image.get_data().at<uint8_t>(0,0),20);
    EXPECT_EQ(clone.get_data().at<uint8_t>(0,0),1);
}
