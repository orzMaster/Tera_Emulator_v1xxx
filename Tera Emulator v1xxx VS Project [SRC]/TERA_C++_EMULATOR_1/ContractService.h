#pragma once

#include <vector>

enum ContractType;
class Contract;
class ContractService
{
public:
	static const bool Initialize();
	static void AddContrct(const Contract const * con);
	static const Contract const * GetContract(ContractType type);
	static unsigned int GetCount();
	static void Release();
private:
	static std::vector<const Contract const*> _contracts;

};

