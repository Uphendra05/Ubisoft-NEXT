#pragma once
class CEntity
{

public :

	CEntity();

	virtual ~CEntity();

	int entityID = 0;

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Cleanup() = 0;
	virtual void OnDestroy() = 0;


};

