#pragma once

template <typename DependentConsumer>
class ThreadedConsumer : public ThreadedActor
{
public:
	template <typename... Args>
	ThreadedConsumer(Args&&... args)
		: ThreadedActor(std::forward<Args>(args)...)
	{
	}

protected:
	void Run() override
	{
		DependentConsumer dependentConsumer(mSynchronizer.mStopper);
		while (!mSynchronizer.IsStopped())
		{
			Mutex mutex;
			UniqueLock<Mutex> lock(mutex);
			mSynchronizer.Wait(mutex);
			if (!mSynchronizer.IsStopped())
				ProcessElement(dependentConsumer);
		}
	}

	void ProcessElement(IConsumer& aDependentConsumer)
	{
		auto element = mSynchronizer.GetQueueElement();
		if (element)
			aDependentConsumer.Consume(std::move(element));
	}
};

