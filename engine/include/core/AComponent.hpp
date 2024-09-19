#include "IComponent.hpp"

namespace potEngine {
    class AComponent : public IComponent {
    public:
        AComponent();
        ~AComponent();
        std::uint32_t getID() const override;
    private:
        std::uint32_t _id;
    };
}