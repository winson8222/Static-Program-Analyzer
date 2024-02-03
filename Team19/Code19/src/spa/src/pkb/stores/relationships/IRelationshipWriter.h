#pragma

template <typename KeyType, typename ValueType>
class IRelationshipWriter {
public:
    virtual void addRelationship(KeyType key, ValueType value) = 0;
};

