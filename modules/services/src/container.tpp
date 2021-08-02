template <typename key_type,typename container_type>
improc::Container<key_type,container_type>::Container() 
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Creating container with {} key and {} container...",typeid(key_type).name(),typeid(container_type).name());
    #endif
}

template <typename key_type,typename container_type>
void improc::Container<key_type,container_type>::Add(const key_type& key, const container_type& item)
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

template <typename key_type,typename container_type>
container_type improc::Container<key_type,container_type>::Get(const key_type& key) const
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Obtaining key {} from container...",key);
    #endif

    if (this->hash_table_.find(key) != this->hash_table_.end())
    {
        return this->hash_table_.at(key);
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

template <typename key_type,typename container_type>
container_type& improc::Container<key_type,container_type>::operator[](const key_type& key)
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Obtaining key {} from container...",key);
    #endif

    return this->hash_table_[key];
}

template <typename key_type,typename container_type>
void improc::Container<key_type,container_type>::Erase(const key_type& key)
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

template <typename key_type,typename container_type>
void improc::Container<key_type,container_type>::Clear()
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Deleting container...");
    #endif

    this->hash_table_.clear();
}

template <typename key_type,typename container_type>
size_t improc::Container<key_type,container_type>::Size() const
{
    #ifdef WITH_DEBUG
    SPDLOG_TRACE("");
    spdlog::trace("Obtaining container size...");
    #endif
    
    return this->hash_table_.size();
}