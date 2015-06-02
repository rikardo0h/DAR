using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PruebaDAR
{
    class ATK
    {
        private byte type = new byte();
        private byte count = new byte();
        private byte ack = new byte();
        private byte[] msg = new byte[100];


        public void setType(byte type)
        {
            this.type = type;
        }

        public byte getType()
        {
            return this.type;
        }

        public void setCount(byte count)
        {
            this.count = count;
        }

        public byte getCount()
        {
            return this.count;
        }

        public void setACK(byte ack)
        {
            this.ack = ack;
        }

        public byte getACK()
        {
            return this.ack;
        }

        public void setMSG(String msg)
        {
            byte [] bTemp = Encoding.ASCII.GetBytes(msg);
            for (int i = 0; i < bTemp.Length; i++)
            {
                this.msg[i] = bTemp[i];
            }
        }

        public byte [] getMSG()
        {
            return this.msg;
        }


        public byte [] ObjetcToArray()
        {
            byte [] arrayATK = new byte[103];
            arrayATK[0] = this.type;
            arrayATK[1] = this.count;
            arrayATK[2] = this.ack;
            for (int i = 0; i < 100; i++)
            {                
                arrayATK[i+3] = this.msg[i];                
            }
            return arrayATK;
        }

        public void ArrayToObjetc(byte [] arr)
        {
            this.type = arr[0];
            this.count = arr[1];
            this.ack = arr[2];
            for (int i = 0; i < this.msg.Length; i++)
            {
                this.msg[i] = arr[i + 3];
            }
        }
    }
}
