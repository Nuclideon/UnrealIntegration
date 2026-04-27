// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"

#include "udError.h"
#include "udPointCloud.h"

#include "Containers/UnrealString.h"
#include "Containers/ResourceArray.h"

static auto GetError = [](udError e) -> FString {
	return FString(UTF8_TO_TCHAR(udError_GetErrorString(e)));
};

template <class Type>
class FUdSDKResourceBulkData : public FResourceBulkDataInterface
{
public:
	FUdSDKResourceBulkData()
	{
		
	}

	void ResizeArray(int32 Size)
	{
		Data.SetNum(Size, EAllowShrinking::No);
		//Data.Empty(Size);
		//Data.AddUninitialized(Size);
	}

	/**
	* @return ptr to the resource memory which has been preallocated
	*/
	virtual const void* GetResourceBulkData() const override
	{
		return Data.GetData();
	}

	Type* GetData()
	{
		return Data.GetData();
	}

	uint32 GetTypeSize()
	{
		return sizeof(Type);
	}

	/**
	* @return size of resource memory
	*/
	virtual uint32 GetResourceBulkDataSize() const override
	{
		return Data.Num() * sizeof(Type);
	}

	/**
	* Free memory after it has been used to initialize RHI resource
	*/
	virtual void Discard() override
	{
		//Data.Empty();
	}

private:
	TArray<Type>	Data;
};
