#include <gtest/gtest.h>

#define WITH_DEBUG
#include <improc/infrastructure/file.h>
#include <improc/services/context.h>
#include <improc/services/base_service.h>
#include <improc/services/factory.h>
#include <improc/services/batch_service.h>

#include <container.cpp>
#include <context.cpp>
#include <base_service.cpp>
#include <factory.cpp>
#include <batch_service.cpp>

class IncrementTestDS : public improc::StringKeyBaseService
{
    public:
        IncrementTestDS() : improc::StringKeyBaseService() {}
        void    Load   (const Json::Value& service_json) override
        {
            this->improc::StringKeyBaseService::Load(service_json);
            spdlog::info("--- INCREMENT SERVICE ---");
            spdlog::info("Input : {}",this->inputs_[0]);
            spdlog::info("Output: {}",this->outputs_[0]);
        }

        void    Run    (improc::StringKeyContext&  context) const override
        {
            context[this->outputs_[0]] = std::any_cast<int>(context.Get(this->inputs_[0])) + 1;
            spdlog::info("Increment Service: ori = {}",std::any_cast<int>(context[this->outputs_[0]]));
        }
};

class SubtractTestDS : public improc::StringKeyBaseService
{
    private: 
        int number_to_subtract_ = 0;

    public:
        SubtractTestDS() : improc::StringKeyBaseService() {}
        void    Load   (const Json::Value& service_json) override
        {
            this->improc::StringKeyBaseService::Load(service_json);

            for (Json::Value::const_iterator service_field_iter = service_json.begin(); service_field_iter != service_json.end(); ++service_field_iter)
            {
                const std::string kNumberKey = "number";
                spdlog::debug("Analyzing field {} for subtract service...",service_field_iter.name());

                if (service_field_iter.name() == kNumberKey)
                {
                    this->number_to_subtract_ = service_field_iter->asInt();
                    break;
                }
            }
            spdlog::info("--- SUBTRACT SERVICE ---");
            spdlog::info("Input : {}",this->inputs_[0]);
            spdlog::info("Output: {}",this->outputs_[0]);
            spdlog::info("Number: {}",this->number_to_subtract_);
        }

        void    Run    (improc::StringKeyContext&  context) const override
        {
            context[this->outputs_[0]] = std::any_cast<int>(context.Get(this->inputs_[0])) - this->number_to_subtract_;
            spdlog::info("Subtract Service: ori = {}",std::any_cast<int>(context[this->outputs_[0]]));
        }
};

class MultiplyTestDS : public improc::StringKeyBaseService
{
    private: 
        int number_to_multiply_ = 1;

    public:
        MultiplyTestDS() : improc::StringKeyBaseService() {}
        void    Load   (const Json::Value& service_json) override
        {
            this->improc::StringKeyBaseService::Load(service_json);

            for (Json::Value::const_iterator service_field_iter = service_json.begin(); service_field_iter != service_json.end(); ++service_field_iter)
            {
                const std::string kNumberKey = "number";
                spdlog::debug("Analyzing field {} for multiply service...",service_field_iter.name());

                if (service_field_iter.name() == kNumberKey)
                {
                    this->number_to_multiply_ = service_field_iter->asInt();
                    break;
                }
            }
            spdlog::info("--- MULTIPLY SERVICE ---");
            spdlog::info("Input : {}",this->inputs_[0]);
            spdlog::info("Output: {}",this->outputs_[0]);
            spdlog::info("Number: {}",this->number_to_multiply_);
        }

        void    Run    (improc::StringKeyContext&  context) const override
        {
            context[this->outputs_[0]] = std::any_cast<int>(context.Get(this->inputs_[0])) * this->number_to_multiply_;
            spdlog::info("Multiply Service: ori = {}",std::any_cast<int>(context[this->outputs_[0]]));
        }
};

TEST(Factory,TestFactoryEmptyConstructor) {
    improc::StringKeyServicesFactory factory {};
    EXPECT_EQ(factory.Size(),0);    
}

TEST(Factory,TestAddItemsToFactory) {
    improc::StringKeyServicesFactory factory {};
    factory.Add("increment",std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<IncrementTestDS>});
    factory.Add("subtract" ,std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<SubtractTestDS>} );
    factory.Add("multiply" ,std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<MultiplyTestDS>} );
    EXPECT_EQ(factory.Size(),3);    
}

TEST(Context,TestContextEmptyConstructor) {
    improc::StringKeyContext cntxt {};
    EXPECT_EQ(cntxt.Size(),0);    
}

TEST(Context,TestAddItemToContext) {
    improc::StringKeyContext cntxt {};
    cntxt.Add("ori",2);
    EXPECT_EQ(cntxt.Size(),1);    
    EXPECT_EQ(std::any_cast<int>(cntxt.Get("ori")),2);
}

TEST(BatchService,TestBatchServiceEmptyConstructor) {
    improc::StringKeyBatchService batch {};
    EXPECT_EQ(batch.Size(),0);    
}

TEST(BatchService,TestBatchServiceLoad) {
    improc::JsonFile json_file {"../../test/test_ex1.json"};
    Json::Value json_content = json_file.Read();

    improc::StringKeyServicesFactory factory {};
    factory.Add("increment",std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<IncrementTestDS>});
    factory.Add("subtract" ,std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<SubtractTestDS>} );
    factory.Add("multiply" ,std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<MultiplyTestDS>} );

    improc::StringKeyBatchService batch {};
    batch.Load(factory,json_content);
    EXPECT_EQ(batch.Size(),4);
}

TEST(BatchService,TestBatchServiceRunWithDuplicateService) {
    improc::JsonFile json_file {"../../test/test_ex1.json"};
    Json::Value json_content = json_file.Read();

    improc::StringKeyServicesFactory factory {};
    factory.Add("increment",std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<IncrementTestDS>});
    factory.Add("subtract" ,std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<SubtractTestDS>} );
    factory.Add("multiply" ,std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<MultiplyTestDS>} );

    improc::StringKeyBatchService batch {};
    batch.Load(factory,json_content);
    EXPECT_EQ(batch.Size(),4);

    improc::StringKeyContext cntxt {};
    cntxt.Add("ori",2);
    spdlog::info("Start, ori = {}",std::any_cast<int>(cntxt.Get("ori")));
    batch.Run(cntxt);    
    EXPECT_EQ(std::any_cast<int>(cntxt.Get("ori")),4);
}