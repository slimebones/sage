#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

class Signal {
public:
	using Slot = std::function<void(void*)>;

	void connect(Slot slot) {
		slots.push_back(slot);
	}

	void disconnect(Slot slot) {
		slots.erase(std::remove_if(
			slots.begin(),
			slots.end(),
			[&slot](const Slot& s) {
				return s.target<void(int)>() == slot.target<void(int)>();
			}
		), slots.end());
	}

	void emit(void* value) {
		for (const auto& slot : slots) {
			slot(value);
		}
	}
private:
	std::vector<Slot> slots;
};