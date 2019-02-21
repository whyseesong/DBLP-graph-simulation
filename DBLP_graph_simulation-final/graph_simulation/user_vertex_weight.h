#pragma once
class user_vertex_weight
{
public:
	user_vertex_weight();
	~user_vertex_weight();

	int getIndex() { return index; }
	int getWeight() { return weight; }

	void setIndex(int _index) { index = _index; }
	void setWeight(int _weight) { weight = _weight; }


	bool operator ==(const user_vertex_weight &u) const {
		return this->weight == u.weight;
	}
	bool operator !=(const user_vertex_weight &u) const {
		return this->weight != u.weight;
	}
	bool operator >(const user_vertex_weight &u) const {
		return this->weight > u.weight;
	}
	bool operator >=(const user_vertex_weight &u) const {
		return this->weight >= u.weight;
	}
	bool operator <(const user_vertex_weight &u) const {
		return this->weight < u.weight;
	}
	bool operator <=(const user_vertex_weight &u) const {
		return this->weight <= u.weight;
	}




private :
	int index;
	int weight;
};

