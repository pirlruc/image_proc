#include <improc/services/container.h>

template <typename key_type>
improc::Container<key_type>::Container() {}

template <typename key_type>
void improc::Container<key_type>::Add(const key_type& key, const std::any& item)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Adding key {} to container...",key);
    #endif

    if (this->hash_table_.find(key) == this->hash_table_.end())
    {
        this->hash_table_[key] = item;
    }
    else
    {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error("ERROR_01: Duplicated key {} in container.",key);
        #endif

        throw improc::duplicated_key();
    }
}

template <typename key_type>
std::any& improc::Container<key_type>::operator[](const key_type& key)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Obtaining key {} from container...",key);
    #endif

    return this->hash_table_[key];
}

template <typename key_type>
std::any improc::Container<key_type>::Get(const key_type& key)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Obtaining key {} from container...",key);
    #endif

    if (this->hash_table_.find(key) != this->hash_table_.end())
    {
        return this->hash_table_[key];
    }
    else
    {
        #ifdef WITH_DEBUG
        SPDLOG_ERROR("");
        spdlog::error("ERROR_02: Key {} not found in container.",key);
        #endif

        throw improc::not_found_key();
    }
}

template <typename key_type>
void improc::Container<key_type>::Erase(const key_type& key)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Deleting key {} from container...",key);
    #endif

    if (this->hash_table_.find(key) != this->hash_table_.end()) 
    {
        this->hash_table_.erase(key);
    }
    else
    {
        #ifdef WITH_DEBUG
        SPDLOG_WARN("");
        spdlog::warn("WARN_01: Key {} not found in container.",key);
        #endif
    }
}

template <typename key_type>
void improc::Container<key_type>::Clear()
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Deleting container...");
    #endif

    this->hash_table_.clear();
}

template <typename key_type>
size_t improc::Container<key_type>::Size() const
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Obtaining container size...");
    #endif
    
    return this->hash_table_.size();
}