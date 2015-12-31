using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace CSharpChannel
{
    class ChannelQueue<T>
    {
        private List<ElemItem<T>> mLstCapcity;
        private List<ElemItem<T>> mLstReadWrite;

        private int mSize;
        private static bool mCanWrite = true;
        private static bool mCanRead = false;
        private static object mObj = new object();

        public ChannelQueue(int iSize, T elm)
        {
            mSize = iSize;
            mLstCapcity = new List<ElemItem<T>>(iSize);
            for(int i = 0; i < iSize; i++)
            {
                mLstCapcity.Add(new ElemItem<T>(elm));
            }
            mLstReadWrite = new List<ElemItem<T>>(iSize);
        }

        // write element into the queue
        public void writeElem(T Elm)
        {
            Monitor.Enter(mObj);

            while(!mCanWrite)
            {
                Monitor.Wait(mObj);
            }

            ElemItem<T> elm = mLstCapcity[0];
            mLstCapcity.RemoveAt(0);

            elm.SetElem(Elm);

            mLstReadWrite.Add(elm);
            mCanRead = true;

            if (mLstCapcity.Count <= 0)
            {
                mCanWrite = false;
            }

            Monitor.PulseAll(mObj);

            Monitor.Exit(mObj);            
        }

        // read element from the queue
        public T readElem()
        {
            Monitor.Enter(mObj);

            while (!mCanRead)
            {
                Monitor.Wait(mObj);
            }

            ElemItem<T> elm = mLstReadWrite[0];
            T ret = elm.GetElem();

            mLstReadWrite.RemoveAt(0);
            mLstCapcity.Add(elm);

            mCanWrite = true;
            if(mLstCapcity.Count >= mSize)
            {
                mCanRead = false;
            }
            Monitor.PulseAll(mObj);

            Monitor.Exit(mObj);

            return ret;           
        }
    }
}
