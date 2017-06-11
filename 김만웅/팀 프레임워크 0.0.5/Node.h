#pragma once
class Node
{
private:
	D3DXVECTOR3 position;
	int via;
	int selfIndex;
	float cost;
	bool visited;

private:
	LPD3DXMESH mesh;
	float radius;
public:
	Node();
	Node(int selfIndex, float cost, int via, Node& temp);
	~Node();

	void Render();

	D3DXVECTOR3 getPosition(void) { return position; }
	void setPosition(D3DXVECTOR3 position) { this->position = position; }

	int getSelfIndex(void) { return selfIndex; }
	void setSelfIndex(int selfIndex) { this->selfIndex = selfIndex; }

	int getVia(void) { return via; }
	void setVia(int via) { this->via = via; }

	float getCost(void) { return cost; }
	void setCost(float cost) { this->cost = cost; }

	bool getVisited(void) { return visited; }
	void setVisited(bool visited) { this->visited = visited; }

	LPD3DXMESH getMesh(void) { return mesh; }
	void setMesh(float radius) 
	{ 
		D3DXCreateSphere(device, radius, 20, 20, &mesh, 0);
		this->radius = radius;
	}

	float getRadius(void) { return radius; }

	//크기 비교 연산자 재정의 >의 결과값을 bool형식으로 리턴한다.
	bool operator>(const Node& v) const
	{
		return cost > v.cost;
	}

	//크기 비교 연산자 재정의 <의 결과값을 bool형식으로 리턴한다.
	bool operator<(const Node& v) const
	{
		return !(cost < v.cost);
	}
};

