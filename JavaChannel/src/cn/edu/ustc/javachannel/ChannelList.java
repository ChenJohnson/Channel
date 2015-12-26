package cn.edu.ustc.javachannel;

import java.util.ArrayList;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

//import com.sun.corba.se.impl.orbutil.concurrent.Mutex;
//import com.sun.xml.internal.bind.v2.schemagen.xmlschema.List;

public class ChannelList<T> {
	private int mSize;
	private ArrayList<ChannelElem<T>> mLeft;
	private ChannelElem<T> mHead;
	private ChannelElem<T> mLast;
	private Condition mCanWrite;
	private Condition mCanRead;
	private Lock mLock;
	
	public ChannelList(int iSize, T elm){
		this.mSize = iSize;
		this.mLeft = new ArrayList<ChannelElem<T>>(iSize);
		
		for (int i = 0; i < iSize; i++) {
			this.mLeft.add(new ChannelElem<T>(elm));
		}
		
		this.mHead = new ChannelElem<T>(elm);
		this.mLast = this.mHead;
		
		this.mLock = new ReentrantLock();
		mCanWrite = mLock.newCondition();
		mCanRead = mLock.newCondition();
		
	}
	
	/*public void setList(T elm){
		for (ChannelElem<T> channelElem : mLeft) {
			channelElem = new ChannelElem<T>(elm);
		}
	}*/
	
	public void writeElem(T elm) throws InterruptedException{
		this.mLock.lock();
		//System.out.println(this.mLeft.size());
		try{
			while(this.mLeft.isEmpty()){
				this.mCanWrite.await();
			}
			ChannelElem<T> t = this.mLeft.get(0);
			this.mLeft.remove(0);
			t.setElem(elm);
			
			this.mLast.setNext(t);
			//t.setPrev(this.mLast);
			this.mLast = t;
			
			this.mCanRead.signal();
			
			if(this.mLeft.size() > 0){
				this.mCanWrite.signal();
			}
		}finally{
			this.mLock.unlock();
		}
	}
	
	public T readElem() throws InterruptedException{
		T ret = null;
		
		this.mLock.lock();
		
		try{
			while(this.mLeft.size() == this.mSize){
				this.mCanRead.await();
			}
			//ret = this.mLast.getElem();
			ChannelElem<T> retElm = this.mHead.getNext();
			ret = retElm.getElem();
			
			if(retElm.getNext() == null){
				this.mLast = this.mHead;
			}else{
				this.mHead.setNext(retElm.getNext());
			}
			
			this.mLeft.add(retElm);		
			
			this.mCanWrite.signal();
			if(this.mLeft.size() < this.mSize){
				this.mCanRead.signal();
			}
			
			return ret;
		}finally{
			this.mLock.unlock();
		}		
	}
}
