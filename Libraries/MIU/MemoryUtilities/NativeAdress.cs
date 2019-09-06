using System;

namespace MemoryUtilities
{
    public class NativeAdress
    {
		public IntPtr Adress {get; set;}
		
		public NativeAdress(IntPtr adress)
		{
			Adress = adress;
		}
		
		public static implicit operator IntPtr(NativeAdress nativeAdress)
			=> nativeAdress.Adress;
		
		public static implicit operator NativeAdress(int adress)
			=> new NativeAdress(new IntPtr(adress));
			
		public static implicit operator NativeAdress(long adress)
			=> new NativeAdress(new IntPtr(adress));

        public static implicit operator NativeAdress(IntPtr adress)
            => new NativeAdress(adress);
    }
}