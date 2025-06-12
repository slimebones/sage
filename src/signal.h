#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

template<typename T>
class Signal {
public:
    using Slot = std::function<void(T)>;

    void connect(Slot slot) {
        slots.push_back(slot);
    }

    void disconnect(Slot slot) {
        slots.erase(std::remove_if(
            slots.begin(),
            slots.end(),
            [&slot](const Slot& s) {
                return s.target<void(T)>() == slot.target<void(T)>();
            }
        ), slots.end());
    }

    void emit(T value) {
        for (const auto& slot : slots) {
            slot(value);
        }
    }
private:
    std::vector<Slot> slots;
};
