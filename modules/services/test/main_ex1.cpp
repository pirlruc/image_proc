#include <improc/services/context.h>
#include <improc/services/base_service.h>

#include <container.cpp>
#include <context.cpp>
#include <base_service.cpp>

#include <iostream>

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

        void    Run    (improc::StringKeyContext&  context) override
        {
            context[this->outputs_[0]] = std::any_cast<int>(context.Get(this->inputs_[0])) + 1;
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
                }
                else 
                {
                    #ifdef WITH_DEBUG
                    SPDLOG_WARN("");
                    spdlog::warn("WARN_01: Member {} not recognized for subtract service.",service_field_iter.name());
                    #endif
                }
            }
            std::cout << "--- SUBTRACT SERVICE ---"     << std::endl;
            std::cout << "Input :" << this->inputs_[0]  << std::endl;
            std::cout << "Output:" << this->outputs_[0] << std::endl;
            std::cout << "Number:" << this->number_to_subtract_ << std::endl;
        }

        void    Run    (improc::StringKeyContext&  context) override
        {
            context[this->outputs_[0]] = std::any_cast<int>(context.Get(this->inputs_[0])) - this->number_to_subtract_;
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
                }
                else 
                {
                    #ifdef WITH_DEBUG
                    SPDLOG_WARN("");
                    spdlog::warn("WARN_01: Member {} not recognized for multiply service.",service_field_iter.name());
                    #endif
                }
            }
            std::cout << "--- MULTIPLY SERVICE ---"     << std::endl;
            std::cout << "Input :" << this->inputs_[0]  << std::endl;
            std::cout << "Output:" << this->outputs_[0] << std::endl;
            std::cout << "Number:" << this->number_to_multiply_ << std::endl;
        }

        void    Run    (improc::StringKeyContext&  context) override
        {
            context[this->outputs_[0]] = std::any_cast<int>(context.Get(this->inputs_[0])) * this->number_to_multiply_;
        }
};

#include <improc/infrastructure/file.h>

struct DataElem
{
    std::string name;
    std::string type;
};

int main()
{
    std::cout << "--- PROTOTYPE EX1 BEGINNING ---" << std::endl;

    const std::string kDataKey      = "data";
    const std::string kServicesKey  = "services";

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

    if (json_content.isMember(kServicesKey) == false) 
    {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error("ERROR_02: Member {} missing on json file.",kServicesKey);
        #endif

        throw improc::file_processing_error();
    }
    Json::Value data_elements    = json_content[kDataKey];
    Json::Value service_elements = json_content[kServicesKey];

    // Obtain list of variables not coming from services
    std::vector<DataElem> input_list {};
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
                spdlog::warn("WARN_03: Member {} not recognized for data element.",elem_field_iter.name());
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

    // Obtain list of services
    std::vector<std::shared_ptr<improc::StringKeyBaseService>> services_list {};
    for (Json::Value::const_iterator srvce_elem_iter = service_elements.begin(); srvce_elem_iter != service_elements.end(); ++srvce_elem_iter)
    {
        const std::string kServiceType = "type";
        const std::string kServiceArgs = "args";

        std::string service_type {};
        Json::Value service_args {};
        for (Json::Value::const_iterator srvce_elem_field_iter = srvce_elem_iter->begin(); srvce_elem_field_iter != srvce_elem_iter->end(); ++srvce_elem_field_iter)
        {
            #ifdef WITH_DEBUG
            SPDLOG_DEBUG("");
            spdlog::debug("Analyzing field {} for service element...",srvce_elem_field_iter.name());
            #endif

            if      (srvce_elem_field_iter.name() == kServiceType)   service_type = srvce_elem_field_iter->asString();
            else if (srvce_elem_field_iter.name() == kServiceArgs)   service_args = *srvce_elem_field_iter;
            else 
            {
                #ifdef WITH_DEBUG
                SPDLOG_WARN("");
                spdlog::warn("WARN_05: Member {} not recognized for service element.",srvce_elem_field_iter.name());
                #endif
            }
        }
        
        if (service_type.empty() == true)
        {
            #ifdef WITH_DEBUG
            SPDLOG_ERROR("");
            spdlog::error("ERROR_06: Member missing for service element.");
            #endif

            throw improc::file_processing_error();
        }

        #ifdef WITH_DEBUG
        SPDLOG_DEBUG("");
        spdlog::debug("Analyzing service element {}...",service_type);
        #endif

        if (service_type == "increment")
        {
            std::shared_ptr<improc::StringKeyBaseService> service {std::make_shared<Increment>(Increment())};
            service->Load(service_args);
            services_list.push_back(service);
        }
        else if (service_type == "subtract")
        {
            std::shared_ptr<improc::StringKeyBaseService> service {std::make_shared<Subtract>(Subtract())};
            service->Load(service_args);
            services_list.push_back(service);
        }
        else if (service_type == "multiply")
        {
            std::shared_ptr<improc::StringKeyBaseService> service {std::make_shared<Multiply>(Multiply())};
            service->Load(service_args);
            services_list.push_back(service);
        }
        else  {
            #ifdef WITH_DEBUG
            SPDLOG_WARN("");
            spdlog::warn("WARN_07: Service {} not recognized.",service_type);
            #endif
        }
    }
    std::cout << "Data number   : " << input_list.size()    << std::endl;
    std::cout << "Service number: " << services_list.size() << std::endl;

    improc::StringKeyContext cntxt {};
    cntxt.Add("ori",2);
    std::cout << "Start, ori = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;

    for (size_t service_idx = 0; service_idx < services_list.size(); service_idx++)
    {
        services_list[service_idx]->Run(cntxt);
        std::cout << "Service ID: " << service_idx << ", ori = " << std::any_cast<int>(cntxt.Get("ori")) << std::endl;
    }
    return 0;
}