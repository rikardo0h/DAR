using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PruebaDAR
{
    class ATK
    {
        private byte type;
        private byte count;
        private byte ack;
        private byte[] msg;

        public ATK()
        {
            type = new byte();
            count = new byte();
            ack = new byte();
            msg = new byte[100];
        }

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
            this.msg = Encoding.ASCII.GetBytes(msg);       
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
            for (int i = 0; i < this.msg.Length; i++)
            {                
                arrayATK[i+3] = this.msg[i];                
            }
            return arrayATK;
        }
    }
}
