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

#include <iostream>
#include <functional>

class Increment : public improc::StringKeyBaseService
{

    public:
        Increment() : improc::StringKeyBaseService() {}
        void    Load   (const Json::Value& service_json) override
        {
            this->improc::StringKeyBaseService::Load(service_json);

            std::cout << "--- INCREMENT SERVICE ---"    << std::endl;
            std::cout << "Input :" << this->inputs_[0]  << std::endl;
            std::cout << "Output:" << this->outputs_[0] << std::endl;
        }

        void    Run    (improc::StringKeyContext&  context) const override
        {
            context[this->outputs_[0]] = std::any_cast<int>(context.Get(this->inputs_[0])) + 1;
            std::cout << "Increment Service: ori = " << std::any_cast<int>(context[this->outputs_[0]]) << std::endl;
        }
};

class Subtract : public improc::StringKeyBaseService
{
    private: 
        int number_to_subtract_ = 0;

    public:
        Subtract() : improc::StringKeyBaseService() {}
        void    Load   (const Json::Value& service_json) override
        {
            this->improc::StringKeyBaseService::Load(service_json);

            for (Json::Value::const_iterator service_field_iter = service_json.begin(); service_field_iter != service_json.end(); ++service_field_iter)
            {
                const std::string kNumberKey = "number";
                
                #ifdef WITH_DEBUG
                SPDLOG_DEBUG("");
                spdlog::debug("Analyzing field {} for subtract service...",service_field_iter.name());
                #endif

                if (service_field_iter.name() == kNumberKey)
                {
                    this->number_to_subtract_ = service_field_iter->asInt();
                    break;
                }
            }
            std::cout << "--- SUBTRACT SERVICE ---"     << std::endl;
            std::cout << "Input :" << this->inputs_[0]  << std::endl;
            std::cout << "Output:" << this->outputs_[0] << std::endl;
            std::cout << "Number:" << this->number_to_subtract_ << std::endl;
        }

        void    Run    (improc::StringKeyContext&  context) const override
        {
            context[this->outputs_[0]] = std::any_cast<int>(context.Get(this->inputs_[0])) - this->number_to_subtract_;
            std::cout << "Subtract Service: ori = " << std::any_cast<int>(context[this->outputs_[0]]) << std::endl;
        }
};

class Multiply : public improc::StringKeyBaseService
{
    private: 
        int number_to_multiply_ = 1;

    public:
        Multiply() : improc::StringKeyBaseService() {}
        void    Load   (const Json::Value& service_json) override
        {
            this->improc::StringKeyBaseService::Load(service_json);

            for (Json::Value::const_iterator service_field_iter = service_json.begin(); service_field_iter != service_json.end(); ++service_field_iter)
            {
                const std::string kNumberKey = "number";

                #ifdef WITH_DEBUG
                SPDLOG_DEBUG("");
                spdlog::debug("Analyzing field {} for multiply service...",service_field_iter.name());
                #endif

                if (service_field_iter.name() == kNumberKey)
                {
                    this->number_to_multiply_ = service_field_iter->asInt();
                    break;
                }
            }
            std::cout << "--- MULTIPLY SERVICE ---"     << std::endl;
            std::cout << "Input :" << this->inputs_[0]  << std::endl;
            std::cout << "Output:" << this->outputs_[0] << std::endl;
            std::cout << "Number:" << this->number_to_multiply_ << std::endl;
        }

        void    Run    (improc::StringKeyContext&  context) const override
        {
            context[this->outputs_[0]] = std::any_cast<int>(context.Get(this->inputs_[0])) * this->number_to_multiply_;
            std::cout << "Multiply Service: ori = " << std::any_cast<int>(context[this->outputs_[0]]) << std::endl;
        }
};

struct DataElem
{
    std::string name;
    std::string type;
};

int main()
{
    std::cout << "--- PROTOTYPE EX1 BEGINNING ---" << std::endl;

    const std::string kDataKey      = "data";

    improc::JsonFile json_file {"../../test/test_ex1.json"};
    Json::Value json_content = json_file.Read();

    if (json_content.isMember(kDataKey) == false) 
    {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error("ERROR_01: Member {} missing on json file.",kDataKey);
        #endif

        throw improc::file_processing_error();
    }


    // Obtain list of variables not coming from services
    Json::Value             data_elements = json_content[kDataKey];
    std::vector<DataElem>   input_list {};
    for (Json::Value::const_iterator data_elem_iter = data_elements.begin(); data_elem_iter != data_elements.end(); ++data_elem_iter)
    {
        const std::string kDataName = "name";
        const std::string kDataType = "type";

        DataElem data {};
        for (Json::Value::const_iterator data_elem_field_iter = data_elem_iter->begin(); data_elem_field_iter != data_elem_iter->end(); ++data_elem_field_iter)
        {
            #ifdef WITH_DEBUG
            SPDLOG_DEBUG("");
            spdlog::debug("Analyzing field {} for data element...",data_elem_field_iter.name());
            #endif

            if      (data_elem_field_iter.name() == kDataName)   data.name = data_elem_field_iter->asString();
            else if (data_elem_field_iter.name() == kDataType)   data.type = data_elem_field_iter->asString();
            else 
            {
                #ifdef WITH_DEBUG
                SPDLOG_WARN("");
                spdlog::warn("WARN_03: Member {} not recognized for data element.",data_elem_field_iter.name());
                #endif
            }
        }
        
        if (data.name.empty() == true || data.type.empty() == true)
        {
            #ifdef WITH_DEBUG
            SPDLOG_ERROR("");
            spdlog::error("ERROR_04: Member missing for data element.");
            #endif

            throw improc::file_processing_error();
        }
        input_list.push_back(data);
    }

    // Define services in factory and load services
    improc::StringKeyServicesFactory factory {};
    factory.Add("increment",std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<Increment>});
    factory.Add("subtract" ,std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<Subtract>} );
    factory.Add("multiply" ,std::function<std::shared_ptr<improc::StringKeyBaseService>(const Json::Value&)> {&improc::LoadServiceFromJson<Multiply>} );
    std::cout << "Factory Size:" << factory.Size() << std::endl;

    improc::StringKeyBatchService batch {};
    batch.Load(factory,json_content);
    std::cout << "Data number   : " << input_list.size()    << std::endl;
    std::cout << "Service number: " << batch.Size()         << std::endl;

    improc::StringKeyContext cntxt {};
    cntxt.Add("ori",2);
    std::cout << "Start, ori = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;
    batch.Run(cntxt);
    return 0;
}