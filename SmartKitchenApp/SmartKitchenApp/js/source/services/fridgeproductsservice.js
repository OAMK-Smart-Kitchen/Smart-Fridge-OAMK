app.service('fridgeproductsservice', [
    '$resource',
    function ($resource) {
        var fridgeProductsService = $resource(app.serviceUrl, { id: '@id' }, {
                //GetProducts: {
                //    url: app.serviceUrl + 'Fridge/Products/:id', //ID from kitchen
                //    method: "GET",
                //    headers: {},
                //    params: {}
                //},
                AddProduct: {
                    url: app.serviceUrl + 'Fridge/Product/:id', //ID from kitchen
                    method: "POST",
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    params: {
                        Name: '@name',
                        IdNFC: '@idnfc',
                        Category: '@category',
                        Calories: '@calories',
                        Quantity: '@quantity',
                        ExpirationDate: '@expirationdate'
                    }
                },
                EditProduct: {
                    url: app.serviceUrl + 'Fridge/Product/Edit/:id', //ID from product
                    method: "PUT",
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    params: {
                        Name: '@name',
                        IdNFC: '@idnfc',
                        Category: '@category',
                        Calories: '@calories',
                        Quantity: '@quantity',
                        ExpirationDate: '@expirationdate'
                    }
                }

            }
        );

        var API = {
            //fridgeProducts: fridgeProductsService.GetProducts,
            addFridgeProduct: fridgeProductsService.AddProduct,
            editFridgeProduct: fridgeProductsService.EditProduct
        };

        return API;
    }
]);