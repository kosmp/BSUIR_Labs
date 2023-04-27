using System.Text.Json;
using MauiApp1.Entities;
using Newtonsoft.Json;

namespace MauiApp1.Services
{
	public class RateService : IRateService
	{
		public HttpClient httpClient;

		public RateService(HttpClient httpClient)
		{
			this.httpClient = httpClient;
		}

		public async Task<IEnumerable<Rate>> GetRates(DateTime date)
		{
			IEnumerable<Rate> result = new List<Rate>();

			Uri uri = new Uri("https://www.nbrb.by/api/exrates/rates" + "?ondate=" + date.ToString("yyyy-MM-dd") + "&periodicity=0");

			HttpResponseMessage response = httpClient.GetAsync(uri).Result;

			if (response.IsSuccessStatusCode)
			{
				string content = response.Content.ReadAsStringAsync().Result;
				result = JsonConvert.DeserializeObject<IEnumerable<Rate>>(content);
			}

			return result;
		}
	}
}
