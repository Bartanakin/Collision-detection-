#pragma once

namespace Barta {

	template<typename List>
	class ReducibleList:public List {
		public:
		void reduce() {
			auto i = this->begin();
			while (i != this->end()) {
				if ((*i)->isToBeDeleted()) {
					i = this->erase(i);
					continue;
				}

				i++;
			}
		}
	};

}