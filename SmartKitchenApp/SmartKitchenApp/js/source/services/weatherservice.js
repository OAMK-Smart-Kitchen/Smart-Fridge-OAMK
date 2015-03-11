app.service('weatherservice', [
    '$http',
    function ($http, $q) {

        return ({
            getWeather: getWeather
        });

        function getWeather(lati, longi) {

            var WeatherURL = "https://api.forecast.io/forecast/f602df518693ebb570099e296b120586/";

            if (lati == undefined || lati == null) {
                lati = "65.0002551";
            };
            if (longi == undefined || longi == null) {
                longi = "25.5098341";
            };

            var request = $.ajax({
                url: WeatherURL + lati + ',' + longi,
                dataType: "jsonp",
                success: function (response) {
                    //console.log(response);
                }
            });

            return (request.then(handleSuccess, handleError));
        };


        // ---
        // PRIVATE METHODS.
        // ---


        // I transform the error response, unwrapping the application dta from
        // the API response payload.
        function handleError(response) {

            // The API response from the server should be returned in a
            // nomralized format. However, if the request was not handled by the
            // server (or what not handles properly - ex. server error), then we
            // may have to normalize it on our end, as best we can.
            if (
                !angular.isObject(response.data) ||
                !response.data.message
                ) {

                return ($q.reject("An unknown error occurred."));

            }

            // Otherwise, use expected error message.
            return ($q.reject(response.data.message));

        }


        // I transform the successful response, unwrapping the application data
        // from the API response payload.
        function handleSuccess(response) {
            return (response);
        }

    }]);

