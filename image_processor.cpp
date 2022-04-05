#include "sources/argparser.h"
#include "sources/logger.h"
#include "sources/filter_factory.h"
#include "additional.h"
#include "sources/image_processing/image_holder.h"

#include "sources/filters/crop.h"
#include "sources/filters/grayscale.h"
#include "sources/filters/edge_detection.h"
#include "sources/filters/negative.h"
#include "sources/filters/sharp.h"
#include "sources/filters/gauss_blur.h"
#include "sources/filters/bilateral.h"

struct CropParams {
    size_t crop_width;
    size_t crop_height;
};

struct EdgeParams {
    size_t edge_threshold;
};

struct BlurParams {
    float blur_sigma;
};

struct BilateralParams {
    float bilateral_diameter;
    float bilateral_sigma_dist;
    float bilateral_sigma_color;
};

struct FilterOptions {
    CropParams crop;
    EdgeParams edge;
    BlurParams blur;
    BilateralParams bilateral;
};


struct FileNames {
    std::string input_filename;
    std::string output_filename;
};

void FillParser(FileNames& files, FilterOptions& options, Parser& parser) {
    parser.AddPositionalArg("input_file", "input file name", &files.input_filename);
    parser.AddPositionalArg("output_file", "output file name", &files.output_filename);

    parser.AddKeywordArg("-gs", "transforms image to shades pf gray");
    parser.AddKeywordArg("-neg", "transforms image to negative");
    parser.AddKeywordArg("-sharp", " improve sharpness of image");

    parser.AddKeywordArg("-crop", "crops image to given height and width. height and with are integer and non-negative", {{"width", &options.crop.crop_width}, {"height", &options.crop.crop_height}});
    parser.AddKeywordArg("-blur", "blurs image based on sigma, sigma - positive number, greater then 1", {{"sigma", &options.blur.blur_sigma}});
    parser.AddKeywordArg("-edge", "paints pixel into black and white based on pixel colors", {{"threshold", &options.edge.edge_threshold}});
    parser.AddKeywordArg("-bilateral", "blurs image, intensity id based on diameter, sigma1, sigma2. All values are positive, greater then 1", {{"diameter", &options.bilateral.bilateral_diameter},
                                        {"sigma1", &options.bilateral.bilateral_sigma_dist},
                                        {"sigma2", &options.bilateral.bilateral_sigma_color}});
}

void RegisterFilters(FilterOptions& options, FilterFactory& factory) {
    auto new_crop_create = std::bind(CreateCropFilter, options.crop.crop_width, options.crop.crop_height);
    factory.Register("-crop", new_crop_create);

    factory.Register("-gs", CreateGrayScaleFilter);

    factory.Register("-neg", CreateNegativeFilter);

    factory.Register("-sharp", CreateSharpFilter);

    auto new_edge_create = std::bind(CreateEdgeDetectionFilter, options.edge.edge_threshold);
    factory.Register("-edge", new_edge_create);

    auto new_blur_create = std::bind(CreateGaussianFilter, options.blur.blur_sigma);
    factory.Register("-blur", new_blur_create);

    auto new_bilateral_create = std::bind(CreateBilateralFilter, options.bilateral.bilateral_diameter,
                                          options.bilateral.bilateral_sigma_dist, options.bilateral.bilateral_sigma_color);
    factory.Register("-bilateral", new_bilateral_create);
}

int main(int argc, char* argv[]) {
    Parser parser;
    try {
        std::vector<std::string> filters_queue;
        FileNames files;
        FilterOptions options;

        FilterFactory factory;

        FillParser(files, options, parser);
        parser.Parse(argc, argv, filters_queue);
        RegisterFilters(options, factory);


        ImageHolder img_holder(CreateImage(files.input_filename), files.output_filename);
        for (const auto &filter: filters_queue) {
            std::unique_ptr<BasicFilter> current = factory.Create(filter);
            current->Apply(&img_holder);
        }

    } catch (std::exception &exception) {
        Logger::Instance().LogError(exception.what());
        std::string info_text = "You have to insert some obligatory arguments: \n";
        info_text += parser.GetArgsDescription(true);
        info_text += "Then you may insert filters names and filter parameters. These are available: \n";
        info_text += parser.GetArgsDescription(false);
        info_text += "!!!Note: if a filter is inserted several times, only the last time is significant";
        Logger::Instance().LogInfo(info_text);
    }
    return 0;
}