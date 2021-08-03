template <typename key_type,typename container_type>
improc::Container<key_type,container_type>::Container() 
{
    SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                      , spdlog::level::trace
                      , "Creating container with {} key and {} container..."
                      , typeid(key_type).name()
                      , typeid(container_type).name() );
}

template <typename key_type,typename container_type>
void improc::Container<key_type,container_type>::Add(const key_type& key, const container_type& item)
{
    SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                      , spdlog::level::trace
                      , "Adding key {} to container...", key );
    if (this->hash_table_.find(key) == this->hash_table_.end())
    {
        this->hash_table_[key] = item;
    }
    else
    {
        SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_01: Duplicated key {} in container.", key );
        throw improc::duplicated_key();
    }
}

template <typename key_type,typename container_type>
container_type improc::Container<key_type,container_type>::Get(const key_type& key) const
{
    SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtaining key {} from container...", key );
    if (this->hash_table_.find(key) != this->hash_table_.end())
    {
        return this->hash_table_.at(key);
    }
    else
    {
        SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_02: Key {} not found in container.", key );
        throw improc::not_found_key();
    }
}

template <typename key_type,typename container_type>
container_type& improc::Container<key_type,container_type>::operator[](const key_type& key)
{
    SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtaining key {} from container...", key );
    return this->hash_table_[key];
}

template <typename key_type,typename container_type>
void improc::Container<key_type,container_type>::Erase(const key_type& key)
{
    SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                      , spdlog::level::trace
                      , "Deleting key {} from container...", key );
    if (this->hash_table_.find(key) != this->hash_table_.end()) 
    {
        this->hash_table_.erase(key);
    }
    else
    {
        SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                          , spdlog::level::warn
                          , "WARN_01: Key {} not found in container.", key );
    }
}

template <typename key_type,typename container_type>
void improc::Container<key_type,container_type>::Clear()
{
    SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                      , spdlog::level::trace
                      , "Deleting container..." );
    this->hash_table_.clear();
}

template <typename key_type,typename container_type>
size_t improc::Container<key_type,container_type>::Size() const
{
    SPDLOG_LOGGER_CALL( improc::ServicesLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtaining container size..." );
    return this->hash_table_.size();
}
