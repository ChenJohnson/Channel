using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSharpChannel
{
    class ElemItem<T>
    {
        private T mElm;
        
        public ElemItem(T elm)
        {
            mElm = elm;
        }

        public void SetElem(T elm)
        {
            mElm = elm;
        }

        public T GetElem()
        {
            return mElm;
        }
    }
}
