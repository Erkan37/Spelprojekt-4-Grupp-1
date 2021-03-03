/*
*	Author: Elia Rönning
*/

#pragma once
#include <vector>
#include <atomic>
#include "RenderCommand.hpp"

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer& aRenderer) = delete;
	~Renderer() = default;

	void Render();

	void PushRenderCommand(const RenderCommand& aRenderCommand);
	void IncrementLogicCounter();
	const std::atomic<uint64_t>& GetRenderCounter() const;
	const std::atomic<uint64_t>& GetLogicCounter() const;

private:
	std::vector<RenderCommand> myBuffer1;
	std::vector<RenderCommand> myBuffer2;
	std::atomic<uint64_t> myCounter;
	std::atomic<uint64_t> myLogicCounter;
};

