#pragma once

class DataStructureBase {
    DataStructureBase(const DataStructureBase&) = delete;
    DataStructureBase(DataStructureBase&&) noexcept = delete;

    DataStructureBase& operator=(const DataStructureBase&) = delete;
    DataStructureBase& operator=(DataStructureBase&&) noexcept = delete;

    public:
        unsigned long long size() const noexcept;

        inline bool isEmpty() const noexcept;

    protected:
        DataStructureBase();
        ~DataStructureBase() noexcept;

    protected:
        unsigned long long mSize{ };
};

DataStructureBase::DataStructureBase() { }
DataStructureBase::~DataStructureBase() noexcept { }

unsigned long long DataStructureBase::size() const noexcept { return mSize; }

inline bool DataStructureBase::isEmpty() const noexcept { return mSize == 0; }