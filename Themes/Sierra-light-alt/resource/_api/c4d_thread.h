/////////////////////////////////////////////////////////////
// CINEMA 4D SDK                                           //
/////////////////////////////////////////////////////////////
// (c) MAXON Computer GmbH, all rights reserved            //
/////////////////////////////////////////////////////////////

#ifndef __C4DTHREAD_H
#define __C4DTHREAD_H

#ifndef __API_INTERN__

#include "operatingsystem.h"

#define ThreadCall(fnc) (this->*C4DOS.Bt->fnc)

struct GeSpinlock
{
	GeSpinlock() : state(0) { }

	volatile Int32 state;

	inline void		 Lock() { ThreadCall(Lock) (); }
	inline void		 Unlock() { ThreadCall(Unlock) (); }
	inline Bool		 AttemptLock() { return ThreadCall(AttemptLock) (); }
};

struct GeRWSpinlock
{
	GeRWSpinlock() : state(0) { }
	volatile Int32 state;

	inline void		 ReadLock() { ThreadCall(ReadLock) (); }
	inline void		 ReadUnlock() { ThreadCall(ReadUnlock) (); }
	inline void		 WriteLock() { ThreadCall(WriteLock) (); }
	inline void		 WriteUnlock() { ThreadCall(WriteUnlock) (); }
	inline Bool		 AttemptWriteLock() { return ThreadCall(AttemptWriteLock) (); }
};

class BaseThread
{
private:
	BaseThread();
	~BaseThread();

public:
	Bool TestBreak(void) { return C4DOS.Bt->TestBreak(this); }
	void End(Bool wait = true) { C4DOS.Bt->End(this, wait); }
	Bool IsRunning(void) { return C4DOS.Bt->IsRunning(this); }
};

class C4DThread
{
	friend class MPThreadPool;
	friend void XThreadMain(void* data);
	friend Bool XThreadTest(void* data);

private:
	Bool				weak;
	BaseThread* bt;

public:
	C4DThread(void);
	virtual ~C4DThread(void);

	BaseThread* Get(void) const { return bt; }

	Bool Start(THREADMODE mode = THREADMODE_ASYNC, THREADPRIORITY priority = THREADPRIORITY_NORMAL);
	void End(Bool wait = true);
	Bool IsRunning(void) { return C4DOS.Bt->IsRunning(bt); }
	Bool TestBreak(void) { return C4DOS.Bt->TestBreak(bt); }
	void Wait(Bool checkevents = false);

	// routines for overriding
	virtual Bool TestDBreak(void) { return false; }
	virtual void Main(void) = 0;
	virtual const Char* GetThreadName(void) = 0;
};

class MPThreadPool
{
private:
	MPBaseThread* mp;
	Int32					mpcount;

public:
	MPThreadPool(void);
	~MPThreadPool(void);

	Bool Init(BaseThread* parent, Int32 count, C4DThread** thread);
	Bool Init(const C4DThread& parent, Int32 count, C4DThread** thread);
	Bool Start(THREADPRIORITY worker_priority);
	C4DThread*	WaitForNextFree(void);
	void Wait(void);
	void End(void);
};

class Semaphore
{
private:
	Semaphore();
	~Semaphore();

public:
	Bool AttemptLock(void) { return C4DOS.Bt->SMLock(this); }
	Bool Lock(BaseThread* bt) { return C4DOS.Bt->SMLockAndWait(this, bt); }
	Bool Lock(C4DThread* bt) { return C4DOS.Bt->SMLockAndWait(this, bt ? bt->Get() : nullptr); }
#ifdef _DEBUG
		#define AttemptLockDebug _AttemptLock(__LINE__, __FILE__)
		#define LockDebug(_x_) _LockDebug(_x_, __LINE__, __FILE__)
	Bool _AttemptLockDebug(Int32 line, const char* file) { return C4DOS.Bt->SMLockDebug(this, line, file); }
	Bool _LockDebug(BaseThread* bt, Int32 line, const char* file) { return C4DOS.Bt->SMLockAndWaitDebug(this, bt, line, file); }
	Bool _LockDebug(C4DThread* bt, Int32 line, const char* file) { return C4DOS.Bt->SMLockAndWaitDebug(this, bt ? bt->Get() : nullptr, line, file); }
#else
		#define AttemptLockDebug AttemptLock
		#define LockDebug(_x_) Lock(_x_)
#endif
	void Unlock(void) { C4DOS.Bt->SMUnlock(this); }

	static Semaphore* Alloc(void);
	static void Free(Semaphore*& sm);
};

class GeSignal
{
private:
	GeSignal();
	~GeSignal();

public:
	Bool Init(SIGNALMODE mode = SIGNALMODE_DEFAULT)
	{
		return ThreadCall(SIGInit) (mode);
	}

	//----------------------------------------------------------------------------------------
	/// Wakes up the thread waiting for this condition.
	/// THREADSAFE.
	//----------------------------------------------------------------------------------------
	void Set()
	{
		ThreadCall(SIGSet) ();
	}

	//----------------------------------------------------------------------------------------
	/// Clears the condition variable.
	/// When Clear() is called after Wait() you must make sure that there are no more threads
	/// still waiting for the same condition. Only after the last thread has left Wait() you are
	/// allowed to call Clear(). Otherwise one of the threads may keep waiting because the
	/// condition was cleared before it was able to wake up.
	//----------------------------------------------------------------------------------------
	void Clear()
	{
		ThreadCall(SIGClear) ();
	}

	//----------------------------------------------------------------------------------------
	/// Waits until the condition has been set or a certain amount of time has passed.
	/// GeSignal is auto-clear by default, this means only one thread can wait for the condition
	/// and the condition is cleared after Wait().
	/// <B> You can only call this from a BaseThread. You are not allowed to wait for a condition
	/// variable from a job - doing this could result in a deadlock.</B>
	/// <B> For compatibility reasons the return value works differently than in [Core]ConditionVariable. </B>
	/// THREADSAFE.
	/// @param[in] timeout						Maximum wait interval in milliseconds (or FOREVER)
	/// @return												Will return true if the wait timed-out, otherwise false.
	//----------------------------------------------------------------------------------------
	Bool Wait(Int32 timeout)
	{
		return ThreadCall(SIGWait) (timeout);
	}

	static GeSignal* Alloc(void);
	static void Free(GeSignal*& sm);
};

inline Int32 GeGetCPUCount(void) { return C4DOS.Bt->GetCPUCount(); }
inline void GeThreadLock(void) { C4DOS.Bt->ThreadLock(); }
inline void GeThreadUnlock(void) { C4DOS.Bt->ThreadUnlock(); }

inline THREADTYPE IdentifyThread(BaseThread* bt) { return C4DOS.Bt->Identify(bt); }

inline UInt32 GeGetCurrentThreadId() { return C4DOS.Bt->GetCurrentThreadId(); }
inline BaseThread* GeGetCurrentThread() { return C4DOS.Bt->GetCurrentThread(); }

#endif
class AutoSpinLock
{
private:
	GeSpinlock*		l;
	AutoSpinLock& operator = (const AutoSpinLock& d);
	AutoSpinLock(AutoSpinLock& data);

public:
	AutoSpinLock(GeSpinlock* lock = nullptr)
	{
		l = nullptr;
		if (!lock)
			return;
		DoLock(lock);
	}

	~AutoSpinLock()
	{
		Unlock();
	}

	void DoLock(GeSpinlock* lock)
	{
		if (l || !lock)
			return;
		lock->Lock();
		l = lock;
	}

	void Unlock(void)
	{
		if (!l)
			return;
		l->Unlock();
		l = nullptr;
	}
};

class AutoLocker;

class AutoLock
{
private:
	friend class AutoLocker;
	GeSpinlock			lock;
	volatile UInt32 threadid;
	AutoLock(const AutoLock& al);
	AutoLock(const AutoLocker& al);

public:
	AutoLock()
	{
		threadid = NOTOK;
	}
};

class AutoLocker
{
private:
	GeSpinlock*			 l;
	volatile UInt32* ct;
	AutoLocker&			 operator = (const AutoLocker& d);
	AutoLocker(AutoLocker& data);

public:
	AutoLocker()
	{
		l	 = nullptr;
		ct = nullptr;
	}
	AutoLocker(AutoLock& data)
	{
		l	 = nullptr;
		ct = nullptr;
		DoLock(data);
	}
	~AutoLocker()
	{
		Unlock();
	}

	void DoLock(AutoLock& data)
	{
		if (l)
			return;

		UInt32 id = GeGetCurrentThreadId();
		if (data.threadid == id)
			return;

		data.lock.Lock();
		l	 = &data.lock;
		ct = &data.threadid;
		if (ct)
			*ct = id;
	}

	void Unlock(void)
	{
		if (!l)
			return;
		*ct = NOTOK;
		l->Unlock();
		l	 = nullptr;
		ct = nullptr;
	}
};

class AutoRWLock
{
	friend class AutoRWLocker;
	GeRWSpinlock		lock;
	volatile UInt32 threadid;

public:
	AutoRWLock()
	{
		threadid = NOTOK;
	}
};


class AutoRWLocker
{
private:
	GeRWSpinlock*		 l;
	volatile UInt32* ct;
	volatile Bool		 is_write;
	AutoRWLocker&		 operator = (const AutoRWLocker& d);
	AutoRWLocker(AutoRWLocker& lock);

public:
	AutoRWLocker()
	{
		l	 = nullptr;
		ct = nullptr;
		is_write = false;
	}
	AutoRWLocker(AutoRWLock& lock, Bool write_lock = true)
	{
		l	 = nullptr;
		ct = nullptr;
		is_write = write_lock;
		DoLock(lock, write_lock);
	}
	~AutoRWLocker()
	{
		Unlock();
	}
	void DoLock(AutoRWLock& lock, Bool write_lock = true)
	{
		if (l)
			return;
		UInt32 id = 0;

		id = GeGetCurrentThreadId();
		if (lock.threadid == id)
			return;

		if (write_lock)
			lock.lock.WriteLock();
		else
			lock.lock.ReadLock();

		is_write = write_lock;
		l	 = &lock.lock;
		ct = &lock.threadid;
		if (ct)
			*ct = id;
	}

	void Unlock(void)
	{
		if (!l)
			return;
		*ct = NOTOK;
		if (is_write)
			l->WriteUnlock();
		else
			l->ReadUnlock();
		l	 = nullptr;
		ct = nullptr;
	}
};

#endif
