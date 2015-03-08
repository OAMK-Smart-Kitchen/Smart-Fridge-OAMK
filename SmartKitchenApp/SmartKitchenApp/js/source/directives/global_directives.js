app.directive('ngConfirmClick', [
    function () {
        return {
            restrict: 'A',
            link: function (scope, element, attr) {
                var msg = attr.ngConfirmClick || "Ben je zeker?";
                var clickAction = attr.confirmedClick;
                element.bind('click',function (event) {
                    bootbox.confirm(msg, function(result) {
                        if(result == true) {
                            scope.$eval(clickAction);
                        }
                    });
                });
            }
        };
    }]);

app.directive('ngEnter', [
    function () {
        return {
            restrict: 'A',
            link: function (scope, element, attrs) {
                element.bind("keydown keypress", function (event) {
                    if(event.which === 13) {
                        scope.$apply(function (){
                            scope.$eval(attrs.ngEnter);
                        });

                        event.preventDefault();
                    }
                });
            }
        };
    }]);

app.directive('capitalize', function() {
   return {
     require: 'ngModel',
     link: function(scope, element, attrs, modelCtrl) {
        var capitalize = function(inputValue) {
           if(inputValue == undefined) inputValue = '';
           var capitalized = inputValue.toUpperCase();
           if(capitalized !== inputValue) {
              modelCtrl.$setViewValue(capitalized);
              modelCtrl.$render();
            }         
            return capitalized;
         }
         modelCtrl.$parsers.push(capitalize);
         capitalize(scope[attrs.ngModel]);  // capitalize initial value
     }
   };
});

app.directive('noCapitalize', function() {
   return {
     require: 'ngModel',
     link: function(scope, element, attrs, modelCtrl) {
        var nocapitalize = function(inputValue) {
           if(inputValue == undefined) inputValue = '';
           var nocapitalized = inputValue.toLowerCase();
           if(nocapitalized !== inputValue) {
              modelCtrl.$setViewValue(nocapitalized);
              modelCtrl.$render();
            }         
            return nocapitalized;
         }
         modelCtrl.$parsers.push(nocapitalize);
         nocapitalize(scope[attrs.ngModel]);  // nocapitalize initial value
     }
   };
});

app.directive('autoCapitalize', function($parse) {
   return {
     require: 'ngModel',
     link: function(scope, element, attrs, modelCtrl) {
        var capitalize = function(inputValue) {
           if (inputValue === undefined) { inputValue = ''; }
           var capitalized = inputValue.charAt(0).toUpperCase() +
                             inputValue.substring(1);
           if(capitalized !== inputValue) {
              modelCtrl.$setViewValue(capitalized);
              modelCtrl.$render();
            }         
            return capitalized;
         }
         modelCtrl.$parsers.push(capitalize);
         capitalize($parse(attrs.ngModel)(scope)); // capitalize initial value
     }
   };
});
app.directive("ngFileSelect", function () {
    return {
        link: function ($scope, el) {
            el.bind("change", function (e) {
                $scope.file = (e.srcElement || e.target).files[0];
                $scope.getFile();
            });
        }
    }
});