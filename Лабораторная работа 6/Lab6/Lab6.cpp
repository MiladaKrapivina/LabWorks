#include <iostream>
#include <httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

void replace(std::string& str, const std::string from, std::string  to, int key)
{
	if (key != 0) to = to.substr(1, key);
	int start_pos = str.find(from);
	if (start_pos == std::string::npos) return;
	str.replace(start_pos, from.length(), to);
}

void gen_response(const httplib::Request& req, httplib::Response& res)
{
	httplib::Client cli("api.openweathermap.org", 80);
	auto result = cli.Get("/data/2.5/forecast?id=693805&units=metric&APPID=07e1054f4a589840494cd54061b1f48d");   // замени APPID=b3b3215efcb4017b119668066e83bc9e на APPID=свой API
	json j;
	if (result && result->status == 200) j = json::parse(result->body);
	std::string HtmlCode;
	std::ifstream stream("informer_template.html");
	getline(stream, HtmlCode, '\0');
	stream.close();

	replace(HtmlCode, "{city.name}", j["city"]["name"].dump(), 10); // 10 так как Simferopol - 10 символов

	for (int i = 0; i < 5; i++)
	{
		int temp = j["list"][0]["dt"];
		for (int i = 0; i < 40; i++) // 40 так как всего 40 объектов в list(5 дней каждые 3 часа, это 8 в день, всего 40)
		{
			if (j["list"][i]["dt"] >= temp)
			{
				replace(HtmlCode, "{list.dt}", j["list"][i]["dt_txt"].dump(), 10);  // 10 так как в записи  xxxx-xx-xx(дата) 10 символов
				replace(HtmlCode, "{list.weather.icon}", j["list"][i]["weather"][0]["icon"].dump(), 3); // 3 так как в записи, например 01n - 3 символа (для картинки)
				replace(HtmlCode, "{list.main.temp}", j["list"][i]["main"]["temp"].dump(), 0);
				temp += 86400;
			}
		}
	}
	res.set_content(HtmlCode, "text/html");
}

int main()
{
	httplib::Server svr;
	svr.Get("/", gen_response);
	svr.listen("localhost", 3000);
}