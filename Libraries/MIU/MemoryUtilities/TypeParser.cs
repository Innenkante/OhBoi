using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace MemoryUtilities
{
    public class TypeParser<T>
    {
        struct Parser<TType>
        {
            public Func<TType, byte[]> ToByteArray { get; set; }
            public Func<byte[], TType> ToType { get; set; }

            public static Parser<TStruct> GenerateStructParser<TStruct>() where TStruct : struct
                => new Parser<TStruct>
                {
                    ToByteArray = TStructValue =>
                    {
                        int sizeOfStructure = Marshal.SizeOf(typeof(TStruct));
                        byte[] array = new byte[sizeOfStructure];

                        IntPtr structurePointer = Marshal.AllocHGlobal(sizeOfStructure);
                        Marshal.StructureToPtr(TStructValue, structurePointer, true);
                        Marshal.Copy(structurePointer, array, 0, sizeOfStructure);

                        Marshal.FreeHGlobal(structurePointer);

                        return array;
                    },
                    ToType = BArrayValue =>
                    {
                        int sizeOfStructure = Marshal.SizeOf(typeof(TStruct));

                        IntPtr structurePointer = Marshal.AllocHGlobal(sizeOfStructure);
                        Marshal.Copy(BArrayValue, 0, structurePointer, sizeOfStructure);

                        TStruct structure = (TStruct)Marshal.PtrToStructure(structurePointer, typeof(TStruct));

                        Marshal.FreeHGlobal(structurePointer);

                        return structure;
                    }
                };
        }

        private Dictionary<Type, object> _parserDictionary = new Dictionary<Type, object>()
        {
            {typeof(byte[]), new Parser<byte[]>
                {
                    ToByteArray = TValue => TValue,
                    ToType = BValue => BValue
                }
            },
            {typeof(int), new Parser<int>
                {
                    ToByteArray = TValue => BitConverter.GetBytes(TValue),
                    ToType = BValue => BitConverter.ToInt32(BValue,0)
                }
            },
            {typeof(string), new Parser<string>
                {
                    ToByteArray = TValue => Encoding.ASCII.GetBytes(TValue),
                    ToType = BValue => Encoding.ASCII.GetString(BValue)
                }
            },
            {typeof(short), new Parser<short>
                {
                   ToByteArray = TValue => BitConverter.GetBytes(TValue),
                   ToType = BValue => BitConverter.ToInt16(BValue,0)
                }
            },
            {typeof(IntPtr), new Parser<IntPtr>
            {
                ToByteArray = TValue => BitConverter.GetBytes(TValue.ToInt32()),
                ToType = BValue => new IntPtr(BitConverter.ToInt32(BValue,0))
            }

            },
            {typeof(WinApi.IMAGE_DOS_HEADER),
                Parser<WinApi.IMAGE_DOS_HEADER>.GenerateStructParser<WinApi.IMAGE_DOS_HEADER>()
            },
            {typeof(WinApi.IMAGE_NT_HEADERS),
                Parser<WinApi.IMAGE_NT_HEADERS>.GenerateStructParser<WinApi.IMAGE_NT_HEADERS>()
            },
            {typeof(WinApi.IMAGE_EXPORT_DIRECTORY),
                Parser<WinApi.IMAGE_EXPORT_DIRECTORY>.GenerateStructParser<WinApi.IMAGE_EXPORT_DIRECTORY>()
            }


        };

        public byte[] ToByteArray(T value)
            => ((Parser<T>)_parserDictionary[typeof(T)]).ToByteArray(value);

        public T ToType(byte[] value)
            => ((Parser<T>)_parserDictionary[typeof(T)]).ToType(value);
    }
}
