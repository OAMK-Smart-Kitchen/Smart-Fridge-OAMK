angular.module('typeFilter', []).filter('typeFilter', function ($filter) {
    return function (input) {
        switch (input) {
            case 0:
                return "Open";
                break;
            case 1:
                return "Woordwolk";
                break;
            case 2:
                return "Afbeelding";
                break;
            case 3:
                return "Meerkeuze";
                break;
            default:
                break;
        }
    };
});