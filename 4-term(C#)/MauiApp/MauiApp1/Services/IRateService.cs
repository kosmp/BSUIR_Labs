using MauiApp1.Entities;

namespace MauiApp1.Services
{
	public interface IRateService
	{
		public Task<IEnumerable<Rate>> GetRates(DateTime date);
	}
}
