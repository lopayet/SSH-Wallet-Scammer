
#include "wshell.h"

static size_t	write_curl_str_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t		realsize = size * nmemb;
	t_curl_str	*mem = (t_curl_str *)userp;
	char		*ptr = realloc(mem->memory, mem->size + realsize + 1);

	if (!ptr) {
		return 0;
	}
	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return realsize;
}

void	curl_init(t_data *data)
{
	curl_global_init(CURL_GLOBAL_ALL);
	data->curl_handle = curl_easy_init();
}

void	set_exchange_rate(t_data *data)
{
	float	rate;
	char	*start;
	int		current_time;

	current_time = time(NULL);
	if (current_time - data->last_rate_refresh < 20)
		return ;
	data->last_rate_refresh = current_time;
	data->curl_str.memory = malloc(1);
	if (!data->curl_str.memory)
		return ;
	data->curl_str.size = 0;
	curl_easy_setopt(data->curl_handle, CURLOPT_URL, "https://bitpay.com/api/rates");
	curl_easy_setopt(data->curl_handle, CURLOPT_WRITEFUNCTION, write_curl_str_callback);
	curl_easy_setopt(data->curl_handle, CURLOPT_WRITEDATA, (void *)&data->curl_str);
	curl_easy_setopt(data->curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	data->curl_res = curl_easy_perform(data->curl_handle);
	if (data->curl_res != CURLE_OK)
	{
		free(data->curl_str.memory);
	}
	else
	{
		start = 0;
		start = strstr(data->curl_str.memory, "\"code\":\"USD\"");
		if (!start)
			return (free(data->curl_str.memory));
		if (sscanf(start, "\"code\":\"USD\",\"name\":\"US Dollar\",\"rate\":%f", &rate) == 1);
			data->rate = rate;
		free(data->curl_str.memory);
	}
}
