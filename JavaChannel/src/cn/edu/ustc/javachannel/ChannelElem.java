package cn.edu.ustc.javachannel;

// defines element in channel
public class ChannelElem<T> {
	private T mElm;
	//private ChannelElem<T> mPrev;
	private ChannelElem<T> mNext;
	
	public ChannelElem (T elm){
		setElem(elm);
		//setPrev(null);
		setNext(null);
	}	
	
	public void setElem(T elm){
		mElm = elm;
	}
	
	public T getElem(){
		return mElm;
	}
	
	/*public void setPrev(ChannelElem<T> prev){
		mPrev = prev;
	}
	
	public ChannelElem<T> getPrev(){
		return mPrev;
	}*/
	
	public void setNext(ChannelElem<T> next){
		mNext = next;
	}
	
	public ChannelElem<T> getNext(){
		return mNext;
	}
}
