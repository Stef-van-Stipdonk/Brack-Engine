    //
    // Created by Stef van Stipdonk on 29/10/2023.
    //

    #ifndef BRACK_ENGINE_SPARSESET_HPP
    #define BRACK_ENGINE_SPARSESET_HPP

    #include "vector"
    #include "../../outfacingInterfaces/IComponentStorage.hpp"

    template <typename T>
    class SparseSet : public IComponentStorage{
    private:
        // Maps entity IDs to dense indices
        std::vector<uint32_t> sparse;

        // Holds components contiguously
        std::vector<T> dense;

        void Insert(uint32_t entity, const T& component);

        T* Get(uint32_t entity);

        void Remove(uint32_t entity);
    public:
        ~SparseSet();

        void removeComponentByEntity(uint32_t entity) override;

        void insertComponent(uint32_t entity, void *component) override;
    };



    #endif //BRACK_ENGINE_SPARSESET_HPP
